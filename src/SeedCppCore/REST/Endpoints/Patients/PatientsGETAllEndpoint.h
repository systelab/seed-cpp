#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerInterface/Model/RequestHeaders.h"


namespace systelab { namespace json_adapter {
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

	class PatientsGetAllEndpoint : public IEndpoint
	{
	public:
		PatientsGetAllEndpoint(const systelab::web_server::RequestHeaders&,
							   model::EntityMgr<model::Patient>&,
							   dal::IJSONTranslatorsFactory&,
							   systelab::json_adapter::IJSONAdapter&,
							   service::IAuthorizationValidatorService&);
		virtual ~PatientsGetAllEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

