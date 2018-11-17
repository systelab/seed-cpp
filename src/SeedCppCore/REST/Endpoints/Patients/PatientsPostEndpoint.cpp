#include "StdAfx.h"
#include "PatientsPostEndpoint.h"

#include "Model/EntityMgr.h"
#include "Model/Patient.h"
#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsPostEndpoint::PatientsPostEndpoint(const systelab::web_server::RequestHeaders& headers,
											   const std::string& requestContent,
											   dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											   systelab::json_adapter::IJSONAdapter& jsonAdapter,
											   service::IAuthorizationValidatorService& authorizationValidatorService,
											   service::IJSONValidatorService& jsonValidatorService,
											   service::IPatientModelService& patientModelService)
		:m_headers(headers)
		,m_requestContent(requestContent)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
		,m_jsonValidatorService(jsonValidatorService)
		,m_patientModelService(patientModelService)
	{
	}

	PatientsPostEndpoint::~PatientsPostEndpoint()
	{
	}

	bool PatientsPostEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsPostEndpoint::execute()
	{
		std::unique_ptr<systelab::json_adapter::IJSONDocument> jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
		if (!jsonRequest)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
		}

		try
		{
			m_jsonValidatorService.validate(*jsonRequest, "JSON_SCHEMA_ENDPOINT_PATIENTS_POST");
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
			auto patientToAdd = std::make_unique<model::Patient>();
			auto patientJSONLoadTranslator = m_jsonTranslatorsFactory.buildPatientLoadTranslator(*patientToAdd);
			patientJSONLoadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

			if (patientToAdd->getDob().is_not_a_date_time())
			{
				patientToAdd->setDob(boost::posix_time::ptime({1970,01,01}));
			}

			const model::Patient& addedPatient = m_patientModelService.addEntity(std::move(patientToAdd));

			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto patientJSONSaveTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(addedPatient);
			patientJSONSaveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

			return ReplyBuilderHelper::build(systelab::web_server::Reply::CREATED, jsonResponse->serialize());
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

