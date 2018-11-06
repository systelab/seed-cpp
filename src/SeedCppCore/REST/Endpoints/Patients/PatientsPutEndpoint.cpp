#include "StdAfx.h"
#include "PatientsPutEndpoint.h"

#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/DAO/ISaveDAO.h"
#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsPutEndpoint::PatientsPutEndpoint(const systelab::web_server::RequestHeaders& headers,
											 const std::string& patientId,
											 const std::string& requestContent,
											 model::EntityMgr<model::Patient>& patientMgr,
											 dal::IDbDAOFactory& dbDAOFactory,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json_adapter::IJSONAdapter& jsonAdapter,
											 service::IAuthorizationValidatorService& authorizationValidatorService,
											 service::IJSONValidatorService& jsonValidatorService)
		:m_headers(headers)
		,m_patientId(patientId)
		,m_requestContent(requestContent)
		,m_patientMgr(patientMgr)
		,m_dbDAOFactory(dbDAOFactory)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
		,m_jsonValidatorService(jsonValidatorService)
	{
	}
	
	PatientsPutEndpoint::~PatientsPutEndpoint()
	{
	}

	bool PatientsPutEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsPutEndpoint::execute()
	{
		std::unique_ptr<systelab::json_adapter::IJSONDocument> jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
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
			jsonRootValue.setType(systelab::json_adapter::OBJECT_TYPE);
			jsonRootValue.addMember("reason", exc.toString());
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST, jsonResponse->serialize());
		}

		try
		{
			const model::Patient* existingPatient = m_patientMgr.getEntityById(m_patientId);
			if (existingPatient)
			{
				auto patientToUpdate = std::make_unique<model::Patient>(*existingPatient);
				auto patientJSONLoadTranslator = m_jsonTranslatorsFactory.buildPatientLoadTranslator(*patientToUpdate);
				patientJSONLoadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

				auto patientSaveDAO = m_dbDAOFactory.buildPatientSaveDAO(*patientToUpdate);
				patientSaveDAO->updateEntity();
				const model::Patient& updatedPatient = m_patientMgr.editEntity(std::move(patientToUpdate));

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

				auto patientSaveDAO = m_dbDAOFactory.buildPatientSaveDAO(*patientToAdd);
				patientSaveDAO->addEntity();
				const model::Patient& addedPatient = m_patientMgr.addEntity(std::move(patientToAdd));

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

