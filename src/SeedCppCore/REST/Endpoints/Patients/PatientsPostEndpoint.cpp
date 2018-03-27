#include "StdAfx.h"
#include "PatientsPostEndpoint.h"

#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/DAO/ISaveDAO.h"
#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsPostEndpoint::PatientsPostEndpoint(const std::string& requestContent,
											   model::EntityMgr<model::Patient>& patientMgr,
											   dal::IDbDAOFactory& dbDAOFactory,
											   dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											   systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_requestContent(requestContent)
		,m_patientMgr(patientMgr)
		,m_dbDAOFactory(dbDAOFactory)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
	{
	}
	
	PatientsPostEndpoint::~PatientsPostEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsPostEndpoint::execute()
	{
		std::unique_ptr<systelab::json_adapter::IJSONDocument> jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
		if (!jsonRequest)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
		}

		// TBD: Validate schema

		try
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
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

