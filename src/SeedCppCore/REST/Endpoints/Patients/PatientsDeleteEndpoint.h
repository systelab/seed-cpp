#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerInterface/Model/RequestHeaders.h"


namespace seed_cpp {
	namespace dal {
		class IDbDAOFactory;
	}
	namespace model {
		class Patient;
	}
	namespace service {
		class IAuthorizationValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class PatientsDeleteEndpoint : public IEndpoint
	{
	public:
		PatientsDeleteEndpoint(const systelab::web_server::RequestHeaders&,
							   const std::string& id,
							   model::EntityMgr<model::Patient>&,
							   dal::IDbDAOFactory&,
							   service::IAuthorizationValidatorService&);
		virtual ~PatientsDeleteEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const std::string m_id;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IDbDAOFactory& m_dbDAOFactory;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

