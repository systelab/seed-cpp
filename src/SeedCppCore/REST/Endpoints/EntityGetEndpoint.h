#pragma once

#include "IEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"

#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"

#include <memory>

namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityMgr>
	class EntityGetEndpoint : public IEndpoint
	{
	private:
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> TranslatorFactoryMethod;
	public:

		EntityGetEndpoint(	const systelab::web_server::RequestHeaders& headers,
							const std::string& entityId,
							_EntityMgr& entityMgr,
							TranslatorFactoryMethod factoryMethod,
							systelab::json::IJSONAdapter& jsonAdapter,
							service::IAuthorizationValidatorService& authorizationValidatorService)
			:m_headers(headers)
			,m_entityId(entityId)
			,m_entityMgr(entityMgr)
			,m_factoryMethod(factoryMethod)
			,m_jsonAdapter(jsonAdapter)
			,m_authorizationValidatorService(authorizationValidatorService)
		{
		}

		virtual ~EntityGetEndpoint() = default;

		bool hasAccess() const override
		{
			return m_authorizationValidatorService.validate(m_headers);
		}

		std::unique_ptr<systelab::web_server::Reply> execute() override
		{
			typename _EntityMgr::SharedLock lock(m_entityMgr);
			const _Entity* entity = m_entityMgr.getEntityById(m_entityId, lock);
			if (!entity)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
			}
			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto translator = m_factoryMethod(*entity);
			translator->saveEntityToJSON(jsonResponse->getRootValue());

			return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
		}

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_entityId;
		_EntityMgr& m_entityMgr;
		TranslatorFactoryMethod m_factoryMethod;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}