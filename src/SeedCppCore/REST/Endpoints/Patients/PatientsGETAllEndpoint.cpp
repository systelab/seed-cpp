#include "StdAfx.h"
#include "PatientsGETAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGETAllEndpoint::PatientsGETAllEndpoint(model::EntityMgr<model::Patient>& patientMgr,
												   dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
												   systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_patientMgr(patientMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
	{
	}
	
	PatientsGETAllEndpoint::~PatientsGETAllEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGETAllEndpoint::execute()
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

		auto reply = std::make_unique<systelab::web_server::Reply>();
		reply->setStatus(systelab::web_server::Reply::OK);
		reply->setContent("PATATA!");

		return reply;
	}

}}

