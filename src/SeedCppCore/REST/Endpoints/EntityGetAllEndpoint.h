#pragma once

#include "IEndpoint.h"
#include "PaginationData.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"
#include "WebServerAdapterInterface/Model/RequestQueryStrings.h"

#include <boost/lexical_cast.hpp>
#include <math.h>


namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityMgr>
	class EntityGetAllEndpoint : public IEndpoint
	{
	private:
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> TranslatorFactoryMethod;

	public:
		EntityGetAllEndpoint(const systelab::web_server::RequestHeaders& headers,
							 const systelab::web_server::RequestQueryStrings& queryStrings,
							 _EntityMgr& entityMgr,
							 TranslatorFactoryMethod factoryMethod,
							 systelab::json::IJSONAdapter& jsonAdapter,
							 service::IAuthorizationValidatorService& authorizationValidatorService)
			:m_headers(headers)
			,m_queryStrings(queryStrings)
			,m_entityMgr(entityMgr)
			,m_factoryMethod(factoryMethod)
			,m_jsonAdapter(jsonAdapter)
			,m_authorizationValidatorService(authorizationValidatorService)
		{
		}

		virtual ~EntityGetAllEndpoint() = default;

		bool hasAccess() const override
		{
			return m_authorizationValidatorService.validate(m_headers);
		}

		std::unique_ptr<systelab::web_server::Reply> execute() override
		{
			auto paginationData = getPaginationData();

			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto& jsonRoot = jsonResponse->getRootValue();
			jsonRoot.setType(systelab::json::OBJECT_TYPE);

			auto jsonContent = jsonRoot.buildValue(systelab::json::ARRAY_TYPE);
			size_t nEntities = paginationData->m_content.size();
			for (size_t i = 0; i < nEntities; ++i)
			{
				const _Entity& entity = paginationData->m_content.at(i);

				auto jsonEntity = jsonRoot.buildValue(systelab::json::OBJECT_TYPE);
				auto translator = m_factoryMethod(entity);
				translator->saveEntityToJSON(*jsonEntity);

				jsonContent->addArrayValue(std::move(jsonEntity));
			}

			jsonRoot.addMember("content",			std::move(jsonContent));
			jsonRoot.addMember("totalElements",		(int)paginationData->m_totalElements);
			jsonRoot.addMember("first",				paginationData->m_first);
			jsonRoot.addMember("last",				paginationData->m_last);
			jsonRoot.addMember("number",			(int)paginationData->m_number);
			jsonRoot.addMember("numberOfElements",	(int)paginationData->m_numberOfElements);
			jsonRoot.addMember("size",				(int)paginationData->m_size);
			jsonRoot.addMember("totalPages",		(int)paginationData->m_totalPages);

			return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
		}

	private:
		std::unique_ptr<PaginationData<_Entity>> getPaginationData() const
		{
			unsigned int page = 0;
			if (m_queryStrings.hasItem("page"))
			{
				try
				{
					page = boost::lexical_cast<unsigned int>(m_queryStrings.getItem("page"));
				}
				catch (std::exception &)
				{
				}
			}

			unsigned int size = 20;
			if (m_queryStrings.hasItem("size"))
			{
				try
				{
					size = boost::lexical_cast<unsigned int>(m_queryStrings.getItem("size"));
				}
				catch (std::exception &)
				{
				}
			}

			std::vector<_Entity> content;
			typename _EntityMgr::SharedLock lock(m_entityMgr);
			unsigned int totalElements = m_entityMgr.count();
			unsigned int indexBegin = page * size;
			unsigned int indexEnd = ((indexBegin + size) < totalElements) ? (indexBegin + size) : totalElements;
			for (unsigned int i = indexBegin; i < indexEnd; ++i)
			{
				content.push_back(*m_entityMgr.getEntity(i, lock));
			}

			auto paginationData = std::make_unique<PaginationData<_Entity>>();
			paginationData->m_content = content;
			paginationData->m_totalElements = totalElements;
			paginationData->m_totalPages = (unsigned int)ceil((double)totalElements / size);
			paginationData->m_number = page;
			paginationData->m_size = size;
			paginationData->m_first = (page == 0);
			paginationData->m_last = (page == (paginationData->m_totalPages - 1));
			paginationData->m_numberOfElements = (unsigned int)content.size();

			return paginationData;
		}

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const systelab::web_server::RequestQueryStrings m_queryStrings;
		_EntityMgr& m_entityMgr;
		TranslatorFactoryMethod m_factoryMethod;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}
