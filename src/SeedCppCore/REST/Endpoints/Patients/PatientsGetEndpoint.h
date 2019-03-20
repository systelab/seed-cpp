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
	}
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsGetEndpoint : public IEndpoint
	{
	public:
		PatientsGetEndpoint(const systelab::web_server::RequestHeaders&,
							const std::string& id,
							model::EntityMgr<model::Patient>&,
							dal::IJSONTranslatorsFactory&,
							systelab::json::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~PatientsGetEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_id;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

