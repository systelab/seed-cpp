#pragma once

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "WebServerAdapterInterface/Model/Reply.h"

#include <memory>


namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityMgr>
	class EntityGetEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> SaveTranslatorFactoryMethod;

		EntityGetEndpoint(_EntityMgr& entityMgr,
						  const SaveTranslatorFactoryMethod& saveTranslatorFactoryMethod,
						  const systelab::json::IJSONAdapter& jsonAdapter)
			:m_entityMgr(entityMgr)
			,m_saveTranslatorFactoryMethod(saveTranslatorFactoryMethod)
			,m_jsonAdapter(jsonAdapter)
		{
		}

		virtual ~EntityGetEndpoint() = default;

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData& requestData) override
		{
			std::string entityId = requestData.getParameters().getStringParameter("id");
			typename _EntityMgr::SharedLock lock(m_entityMgr);
			const _Entity* entity = m_entityMgr.getEntityById(entityId, lock);
			if (!entity)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
			}

			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto translator = m_saveTranslatorFactoryMethod(*entity);
			translator->saveEntityToJSON(jsonResponse->getRootValue());

			return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
		}

	private:
		_EntityMgr& m_entityMgr;
		const SaveTranslatorFactoryMethod m_saveTranslatorFactoryMethod;
		const systelab::json::IJSONAdapter& m_jsonAdapter;
	};

}}