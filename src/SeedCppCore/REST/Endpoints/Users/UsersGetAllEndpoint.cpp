#include "stdafx.h"
#include "UsersGetAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"

#include <boost/lexical_cast.hpp>
#include <math.h>


namespace seed_cpp { namespace rest {

	UsersGetAllEndpoint::UsersGetAllEndpoint(const systelab::web_server::RequestHeaders& headers,
											 const systelab::web_server::RequestQueryStrings& queryStrings,
											 model::EntityMgr<model::User>& userMgr,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json::IJSONAdapter& jsonAdapter,
											 service::IAuthorizationValidatorService& authorizationValidatorService)
		:m_headers(headers)
		,m_queryStrings(queryStrings)
		,m_userMgr(userMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
	{
	}
	
	UsersGetAllEndpoint::~UsersGetAllEndpoint() = default;

	bool UsersGetAllEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> UsersGetAllEndpoint::execute()
	{
		auto paginationData = getPaginationData();

		auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
		systelab::json::IJSONValue& jsonRoot = jsonResponse->getRootValue();
		jsonRoot.setType(systelab::json::OBJECT_TYPE);

		auto jsonContent = jsonRoot.buildValue(systelab::json::ARRAY_TYPE);
		size_t nUsers = paginationData->m_content.size();
		for (size_t i = 0; i < nUsers; i++)
		{
			const model::User& user = (paginationData->m_content)[i];

			auto jsonUser = jsonRoot.buildValue(systelab::json::OBJECT_TYPE);
			auto userTranslator = m_jsonTranslatorsFactory.buildUserSaveTranslator(user);
			userTranslator->saveEntityToJSON(*jsonUser);

			jsonContent->addArrayValue(std::move(jsonUser));
		}

		jsonRoot.addMember("content", std::move(jsonContent));
		jsonRoot.addMember("totalElements", (int) paginationData->m_totalElements);
		jsonRoot.addMember("first", paginationData->m_first);
		jsonRoot.addMember("last", paginationData->m_last);
		jsonRoot.addMember("number", (int) paginationData->m_number);
		jsonRoot.addMember("numberOfElements", (int) paginationData->m_numberOfElements);
		jsonRoot.addMember("size", (int) paginationData->m_size);
		jsonRoot.addMember("totalPages", (int) paginationData->m_totalPages);

		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
	}

	std::unique_ptr<UsersGetAllEndpoint::PaginationData> UsersGetAllEndpoint::getPaginationData() const
	{
		unsigned int page = 0;
		if (m_queryStrings.hasItem("page"))
		{
			try
			{
				page = boost::lexical_cast<unsigned int>(m_queryStrings.getItem("page"));
			}
			catch (std::exception&)
			{}
		}

		unsigned int size = 20;
		if (m_queryStrings.hasItem("size"))
		{
			try
			{
				size = boost::lexical_cast<unsigned int>(m_queryStrings.getItem("size"));
			}
			catch (std::exception&)
			{}
		}

		std::vector<model::User> content;
		model::EntityMgr<model::User>::SharedLock readLock(m_userMgr);
		unsigned int totalElements = m_userMgr.count();
		unsigned int indexBegin = page * size;
		unsigned int indexEnd = ((indexBegin + size) < totalElements) ? (indexBegin + size) : totalElements;
		for (unsigned int i = indexBegin; i < indexEnd; i++)
		{
			content.push_back(*m_userMgr.getEntity(i, readLock));
		}

		auto paginationData = std::make_unique<PaginationData>();
		paginationData->m_content = content;
		paginationData->m_totalElements = totalElements;
		paginationData->m_totalPages = (unsigned int) ceil((double) totalElements / size);
		paginationData->m_number = page;
		paginationData->m_size = size;
		paginationData->m_first = (page == 0);
		paginationData->m_last = (page == (paginationData->m_totalPages - 1));
		paginationData->m_numberOfElements = (unsigned int) content.size();

		return paginationData;
	}

}}

