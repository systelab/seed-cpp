#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp {
	namespace dal {
		class IDbDAOFactory;
	}
	namespace model {
		class Patient;
	}
}

namespace seed_cpp { namespace rest {

	class PatientsDeleteEndpoint : public IEndpoint
	{
	public:
		PatientsDeleteEndpoint(unsigned int id,
							   model::EntityMgr<model::Patient>&,
							   dal::IDbDAOFactory&);
		virtual ~PatientsDeleteEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		unsigned int m_id;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IDbDAOFactory& m_dbDAOFactory;
	};

}}

