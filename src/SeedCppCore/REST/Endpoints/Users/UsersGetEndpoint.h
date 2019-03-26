#pragma once

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
		class User;
		class UserMgr;
	}
	namespace service {
		class IAuthorizationValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class UsersGetEndpoint : public IEndpoint
	{
	public:
		UsersGetEndpoint(const systelab::web_server::RequestHeaders&,
							const std::string& id,
							model::UserMgr&,
							dal::IJSONTranslatorsFactory&,
							systelab::json::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~UsersGetEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_id;
		model::UserMgr& m_userMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

