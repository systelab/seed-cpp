#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class Patient;
	}
	namespace service {
		class IAuthorizationValidatorService;
	}
}

namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsGetEndpoint : public IEndpoint
	{
	public:
		PatientsGetEndpoint(unsigned int id,
							model::EntityMgr<model::Patient>&,
							dal::IJSONTranslatorsFactory&,
							systelab::json_adapter::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~PatientsGetEndpoint();

		bool hasAccess(const std::string& token);
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		unsigned int m_id;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

