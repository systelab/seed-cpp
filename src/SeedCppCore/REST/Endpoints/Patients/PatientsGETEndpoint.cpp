#include "StdAfx.h"
#include "PatientsGETEndpoint.h"

#include "Model/Patient.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	PatientsGETEndpoint::PatientsGETEndpoint(unsigned int id,
											 model::EntityMgr<model::Patient>& patientMgr)
		:m_id(id)
		,m_patientMgr(patientMgr)
	{
	}
	
	PatientsGETEndpoint::~PatientsGETEndpoint()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsGETEndpoint::execute()
	{
		auto reply = std::make_unique<systelab::web_server::Reply>();
		reply->setStatus(systelab::web_server::Reply::OK);
		reply->setContent("PATATA!");
		return reply;
	}

}}

