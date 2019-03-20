#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerAdapterInterface/Model/RequestHeaders.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class Patient;
	}
	namespace service {
		class IAuthorizationValidatorService;
		class IJSONValidatorService;
		class IPatientModelService;
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
							dal::IJSONTranslatorsFactory&,
							systelab::json::IJSONAdapter&,
							service::IAuthorizationValidatorService&,
							service::IJSONValidatorService&,
							service::IPatientModelService&);
		virtual ~PatientsPutEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_patientId;
		std::string m_requestContent;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
		service::IJSONValidatorService& m_jsonValidatorService;
		service::IPatientModelService& m_patientModelService;
	};

}}

