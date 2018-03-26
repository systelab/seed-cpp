#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsGETEndpoint : public IEndpoint
	{
	public:
		PatientsGETEndpoint(unsigned int id, model::EntityMgr<model::Patient>&);
		virtual ~PatientsGETEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		model::EntityMgr<model::Patient>& m_patientMgr;
		unsigned int m_id;
	};

}}

