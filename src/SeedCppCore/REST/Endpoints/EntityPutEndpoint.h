#pragma once

#include "IEndpoint.h"

#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	template <typename _Entity, typename _EntityModelService>
	class EntityPutEndpoint : public IEndpoint
	{
	private:
		typedef std::function<std::unique_ptr<dal::IJSONLoadTranslator>(_Entity&)> LoadTranslatorFactoryMethod;
		typedef std::function<std::unique_ptr<dal::IJSONSaveTranslator>(const _Entity&)> SaveTranslatorFactoryMethod;
	public:
		EntityPutEndpoint(const systelab::web_server::RequestHeaders& headers,
						  const std::string& entityId,
						  const std::string& requestContent,
						  const std::string& schema,
						  _EntityModelService& entityModelService,
						  LoadTranslatorFactoryMethod loadFactoryMethod,
						  SaveTranslatorFactoryMethod saveFactoryMethod,
						  systelab::json::IJSONAdapter& jsonAdapter,
						  service::IAuthorizationValidatorService& authorizationValidatorService,
						  service::IJSONValidatorService& jsonValidatorService)
			:m_headers(headers)
			,m_entityId(entityId)
			,m_requestContent(requestContent)
			,m_schema(schema)
			,m_entityModelService(entityModelService)
			,m_loadFactoryMethod(loadFactoryMethod)
			,m_saveFactoryMethod(saveFactoryMethod)
			,m_jsonAdapter(jsonAdapter)
			,m_authorizationValidatorService(authorizationValidatorService)
			,m_jsonValidatorService(jsonValidatorService)
		{
		}

		~EntityPutEndpoint() = default;

		bool hasAccess() const override
		{
			return m_authorizationValidatorService.validate(m_headers);
		}

		std::unique_ptr<systelab::web_server::Reply> execute() override
		{
			auto jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
			if (!jsonRequest)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
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
				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto lock = m_entityModelService.createWriteLock();
				const _Entity* existingEntity = m_entityModelService.getEntityById(m_entityId, *lock);
				if (existingEntity)
				{
					// Replace existing entity
					auto entityToUpdate = std::make_unique<_Entity>(*existingEntity);
					auto loadTranslator = m_loadFactoryMethod(*entityToUpdate);
					loadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

					const _Entity& updatedEntity = m_entityModelService.editEntity(std::move(entityToUpdate), *lock);

					auto saveTranslator = m_saveFactoryMethod(updatedEntity);
					saveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

					return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
				}
				else
				{
					// Create new entity as if was a POST
					auto entityToAdd = std::make_unique<_Entity>();
					auto loadTranslator = m_loadFactoryMethod(*entityToAdd);
					loadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

					const _Entity& addedEntity = m_entityModelService.addEntity(std::move(entityToAdd), *lock);

					auto saveTranslator = m_saveFactoryMethod(addedEntity);
					saveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

					return ReplyBuilderHelper::build(systelab::web_server::Reply::CREATED, jsonResponse->serialize());
				}
			}
			catch (std::exception& exc)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
			}
		}

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_entityId;
		std::string m_requestContent;
		std::string m_schema;
		_EntityModelService& m_entityModelService;
		LoadTranslatorFactoryMethod m_loadFactoryMethod;
		SaveTranslatorFactoryMethod m_saveFactoryMethod;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
		service::IJSONValidatorService& m_jsonValidatorService;
	};

}}
