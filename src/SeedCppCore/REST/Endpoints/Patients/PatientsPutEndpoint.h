#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp {
	namespace dal {
		class IDbDAOFactory;
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

	class PatientsPutEndpoint : public IEndpoint
	{
	public:
		PatientsPutEndpoint(unsigned int patientId,
							const std::string& requestContent,
							model::EntityMgr<model::Patient>&,
							dal::IDbDAOFactory&,
							dal::IJSONTranslatorsFactory&,
							systelab::json_adapter::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~PatientsPutEndpoint();

		bool hasAccess(const std::string& token);
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		unsigned int m_patientId;
		std::string m_requestContent;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IDbDAOFactory& m_dbDAOFactory;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

