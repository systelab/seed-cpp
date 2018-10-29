#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerInterface/Model/RequestHeaders.h"


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

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

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsPutEndpoint : public IEndpoint
	{
	public:
		PatientsPutEndpoint(const systelab::web_server::RequestHeaders&,
							const std::string& patientId,
							const std::string& requestContent,
							model::EntityMgr<model::Patient>&,
							dal::IDbDAOFactory&,
							dal::IJSONTranslatorsFactory&,
							systelab::json_adapter::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~PatientsPutEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_patientId;
		std::string m_requestContent;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IDbDAOFactory& m_dbDAOFactory;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

