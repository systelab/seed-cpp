#include "stdafx.h"
#include "PatientsPutEndpoint.h"

#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"
#include "Model/PatientMgr.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsPutEndpoint::PatientsPutEndpoint(const systelab::web_server::RequestHeaders& headers,
											 const std::string& patientId,
											 const std::string& requestContent,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json::IJSONAdapter& jsonAdapter,
											 service::IAuthorizationValidatorService& authorizationValidatorService,
											 service::IJSONValidatorService& jsonValidatorService,
											 service::IPatientModelService& patientModelService)
		:m_headers(headers)
		,m_patientId(patientId)
		,m_requestContent(requestContent)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
		,m_jsonValidatorService(jsonValidatorService)
		,m_patientModelService(patientModelService)
	{
	}
	
	PatientsPutEndpoint::~PatientsPutEndpoint() = default;

	bool PatientsPutEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsPutEndpoint::execute()
	{
		std::unique_ptr<systelab::json::IJSONDocument> jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
		if (!jsonRequest)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
		}

		try
		{
			m_jsonValidatorService.validate(*jsonRequest, "JSON_SCHEMA_ENDPOINT_PATIENTS_PUT");
		}
		catch(service::IJSONValidatorService::JSONValidationException& exc)
		{
			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto& jsonRootValue = jsonResponse->getRootValue();
			jsonRootValue.setType(systelab::json::OBJECT_TYPE);
			jsonRootValue.addMember("reason", exc.toString());
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST, jsonResponse->serialize());
		}

		try
		{
			model::PatientMgr::UniqueLock writeLock(m_patientModelService.getEntityMgr());
			const model::Patient* existingPatient = m_patientModelService.getEntityById(m_patientId, writeLock);
			if (existingPatient)
			{
				auto patientToUpdate = std::make_unique<model::Patient>(*existingPatient);
				auto patientJSONLoadTranslator = m_jsonTranslatorsFactory.buildPatientLoadTranslator(*patientToUpdate);
				patientJSONLoadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

				const model::Patient& updatedPatient = m_patientModelService.editEntity(std::move(patientToUpdate), writeLock);

				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto patientJSONSaveTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(updatedPatient);
				patientJSONSaveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

				return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
			}
			else
			{
				auto patientToAdd = std::make_unique<model::Patient>();
				auto patientJSONLoadTranslator = m_jsonTranslatorsFactory.buildPatientLoadTranslator(*patientToAdd);
				patientJSONLoadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

				const model::Patient& addedPatient = m_patientModelService.editEntity(std::move(patientToAdd), writeLock);

				auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
				auto patientJSONSaveTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(addedPatient);
				patientJSONSaveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

				return ReplyBuilderHelper::build(systelab::web_server::Reply::CREATED, jsonResponse->serialize());
			}
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

