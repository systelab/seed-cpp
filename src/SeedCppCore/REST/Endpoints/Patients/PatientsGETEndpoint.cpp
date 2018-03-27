#include "StdAfx.h"
#include "PatientsGetEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGetEndpoint::PatientsGetEndpoint(unsigned int id,
											 model::EntityMgr<model::Patient>& patientMgr,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_id(id)
		,m_patientMgr(patientMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
	{
	}
	
	PatientsGetEndpoint::~PatientsGetEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGetEndpoint::execute()
	{
		const model::Patient* patient = m_patientMgr.getEntityById(m_id);
		if (!patient)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
		}

		auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
		auto patientTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(*patient);
		patientTranslator->saveEntityToJSON(jsonResponse->getRootValue());

		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
	}

}}

