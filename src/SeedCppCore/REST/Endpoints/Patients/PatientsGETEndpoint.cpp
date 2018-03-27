#include "StdAfx.h"
#include "PatientsGETEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Patient.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGETEndpoint::PatientsGETEndpoint(unsigned int id,
											 model::EntityMgr<model::Patient>& patientMgr,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_id(id)
		,m_patientMgr(patientMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
	{
	}
	
	PatientsGETEndpoint::~PatientsGETEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGETEndpoint::execute()
	{
		const model::Patient* patient = m_patientMgr.getEntityById(m_id);
		if (!patient)
		{
			auto reply = std::make_unique<systelab::web_server::Reply>();
			reply->setStatus(systelab::web_server::Reply::NOT_FOUND);
			return reply;
		}

		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();
		systelab::json_adapter::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(systelab::json_adapter::OBJECT_TYPE);

		auto patientTranslator = m_jsonTranslatorsFactory.buildPatientSaveTranslator(*patient);
		patientTranslator->saveEntityToJSON(jsonRoot);

		auto reply = std::make_unique<systelab::web_server::Reply>();
		reply->setStatus(systelab::web_server::Reply::OK);
		reply->setContent(jsonDocument->serialize());

		return reply;
	}

}}

