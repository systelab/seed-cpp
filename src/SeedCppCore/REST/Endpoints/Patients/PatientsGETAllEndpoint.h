#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsGETAllEndpoint : public IEndpoint
	{
	public:
		PatientsGETAllEndpoint(model::EntityMgr<model::Patient>&);
		virtual ~PatientsGETAllEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		model::EntityMgr<model::Patient>& m_patientMgr;
	};

}}

