#include "StdAfx.h"
#include "PatientsGetAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGetAllEndpoint::PatientsGetAllEndpoint(model::EntityMgr<model::Patient>& patientMgr,
												   dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
												   systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_patientMgr(patientMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
	{
	}
	
	PatientsGetAllEndpoint::~PatientsGetAllEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGetAllEndpoint::execute()
	{
		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();
		systelab::json_adapter::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(systelab::json_adapter::ARRAY_TYPE);

		unsigned int nPatients = m_patientMgr.count();
		for (unsigned int i = 0; i < nPatients; i++)
		{
			const model::Patient* patient = m_patientMgr.getEntity(i);

			auto jsonPatient = jsonRoot.buildValue(systelab::json_adapter::OBJECT_TYPE);
			auto patientTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(*patient);
			patientTranslator->saveEntityToJSON(*jsonPatient);

			jsonRoot.addArrayValue(std::move(jsonPatient));
		}

		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonDocument->serialize());
	}

}}

