#include "StdAfx.h"
#include "PatientsGETAllEndpoint.h"

#include "Model/Patient.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGETAllEndpoint::PatientsGETAllEndpoint(model::EntityMgr<model::Patient>& patientMgr)
		:m_patientMgr(patientMgr)
	{
	}
	
	PatientsGETAllEndpoint::~PatientsGETAllEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGETAllEndpoint::execute()
	{
		auto reply = std::make_unique<systelab::web_server::Reply>();
		reply->setStatus(systelab::web_server::Reply::OK);
		reply->setContent("PATATA!");
		return reply;
	}

}}

