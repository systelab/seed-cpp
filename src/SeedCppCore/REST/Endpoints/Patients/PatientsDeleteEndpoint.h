#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "Model/RequestHeaders.h"


namespace seed_cpp { namespace service {
	class IAuthorizationValidatorService;
	class IPatientModelService;
}}

namespace seed_cpp { namespace rest {

	class PatientsDeleteEndpoint : public IEndpoint
	{
	public:
		PatientsDeleteEndpoint(const systelab::web_server::RequestHeaders&,
							   const std::string& id,
							   service::IPatientModelService&,
							   service::IAuthorizationValidatorService&);
		virtual ~PatientsDeleteEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const std::string m_id;
		service::IPatientModelService& m_patientModelService;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

