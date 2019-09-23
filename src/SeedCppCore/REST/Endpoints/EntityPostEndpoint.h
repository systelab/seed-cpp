#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "SeedCppCore/DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "SeedCppCore/REST/Helpers/ReplyBuilderHelper.h"
#include "SeedCppCore/Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityModelService>
	class EntityPostEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		typedef std::function<std::unique_ptr<dal::IJSONLoadTranslator>(_Entity&)> LoadTranslatorFactoryMethod;
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> SaveTranslatorFactoryMethod;

		EntityPostEndpoint(const std::string& schema,
						   _EntityModelService& entityModelService,
						   const LoadTranslatorFactoryMethod& loadFactoryMethod,
						   const SaveTranslatorFactoryMethod& saveFactoryMethod,
						   const service::IJSONValidatorService& jsonValidatorService,
						   const systelab::json::IJSONAdapter& jsonAdapter)
			:m_schema(schema)
			,m_entityModelService(entityModelService)
			,m_loadFactoryMethod(loadFactoryMethod)
			,m_saveFactoryMethod(saveFactoryMethod)
			,m_jsonValidatorService(jsonValidatorService)
			,m_jsonAdapter(jsonAdapter)
		{
		}

		virtual ~EntityPostEndpoint() = default;

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData& requestData) override
		{
			std::string content = requestData.getContent();
			auto jsonRequest = m_jsonAdapter.buildDocumentFromString(content);
			if (!jsonRequest)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST, "{}");
			}

			try
			{
				m_jsonValidatorService.validate(*jsonRequest, m_schema);
			}
			catch (service::IJSONValidatorService::JSONValidationException& exc)
			{
				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto& jsonRootValue = jsonResponse->getRootValue();
				jsonRootValue.setType(systelab::json::OBJECT_TYPE);
				jsonRootValue.addMember("reason", exc.toString());
				return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST, jsonResponse->serialize());
			}

			try
			{
				auto entityToAdd = std::make_unique<_Entity>();
				auto loadTranslator = m_loadFactoryMethod(*entityToAdd);
				loadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

				auto lock = m_entityModelService.createWriteLock();
				const _Entity& addedEntity = m_entityModelService.addEntity(std::move(entityToAdd), *lock);

				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto& jsonRootValue = jsonResponse->getRootValue();
				jsonRootValue.setType(systelab::json::OBJECT_TYPE);
				auto saveTranslator = m_saveFactoryMethod(addedEntity);
				saveTranslator->saveEntityToJSON(jsonRootValue);

				return ReplyBuilderHelper::build(systelab::web_server::Reply::CREATED, jsonResponse->serialize());
			}
			catch (std::exception& exc)
			{
				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto& jsonRootValue = jsonResponse->getRootValue();
				jsonRootValue.setType(systelab::json::OBJECT_TYPE);
				jsonRootValue.addMember("exception", exc.what());
				return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, jsonResponse->serialize());
			}
		}

	private:
		const std::string m_schema;
		_EntityModelService& m_entityModelService;
		const LoadTranslatorFactoryMethod m_loadFactoryMethod;
		const SaveTranslatorFactoryMethod m_saveFactoryMethod;
		const service::IJSONValidatorService& m_jsonValidatorService;
		const systelab::json::IJSONAdapter& m_jsonAdapter;
	};

}}
