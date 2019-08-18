#pragma once


#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "REST/Endpoints/PaginationData.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"
#include "WebServerAdapterInterface/Model/RequestQueryStrings.h"

#include <boost/lexical_cast.hpp>
#include <math.h>


namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityMgr>
	class EntityGetAllEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> SaveTranslatorFactoryMethod;

		EntityGetAllEndpoint(_EntityMgr& entityMgr,
							 const SaveTranslatorFactoryMethod& saveTranslatorFactoryMethod,
							 const systelab::json::IJSONAdapter& jsonAdapter)
			:m_entityMgr(entityMgr)
			,m_saveTranslatorFactoryMethod(saveTranslatorFactoryMethod)
			,m_jsonAdapter(jsonAdapter)
		{
		}

		virtual ~EntityGetAllEndpoint() = default;

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData& requestData) override
		{
			auto paginationData = getPaginationData(requestData.getQueryStrings());

			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto& jsonRoot = jsonResponse->getRootValue();
			jsonRoot.setType(systelab::json::OBJECT_TYPE);

			auto jsonContent = jsonRoot.buildValue(systelab::json::ARRAY_TYPE);
			size_t nEntities = paginationData->m_content.size();
			for (size_t i = 0; i < nEntities; ++i)
			{
				const _Entity& entity = paginationData->m_content.at(i);

				auto jsonEntity = jsonRoot.buildValue(systelab::json::OBJECT_TYPE);
				auto translator = m_saveTranslatorFactoryMethod(entity);
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
		std::unique_ptr<PaginationData<_Entity>> getPaginationData(const systelab::web_server::RequestQueryStrings& queryStrings) const
		{
			unsigned int page = 0;
			if (queryStrings.hasItem("page"))
			{
				try
				{
					page = boost::lexical_cast<unsigned int>(queryStrings.getItem("page"));
				}
				catch (std::exception&)
				{
				}
			}

			unsigned int size = 20;
			if (queryStrings.hasItem("size"))
			{
				try
				{
					size = boost::lexical_cast<unsigned int>(queryStrings.getItem("size"));
				}
				catch (std::exception&)
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
		_EntityMgr& m_entityMgr;
		const SaveTranslatorFactoryMethod m_saveTranslatorFactoryMethod;
		const systelab::json::IJSONAdapter& m_jsonAdapter;
	};

}}
