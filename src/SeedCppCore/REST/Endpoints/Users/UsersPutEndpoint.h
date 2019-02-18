#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "Model/RequestHeaders.h"


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class User;
	}
	namespace service {
		class IAuthorizationValidatorService;
		class IJSONValidatorService;
		class IUserModelService;
	}
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class UsersPutEndpoint : public IEndpoint
	{
	public:
		UsersPutEndpoint(const systelab::web_server::RequestHeaders&,
						 const std::string& userId,
						 const std::string& requestContent,
						 dal::IJSONTranslatorsFactory&,
						 systelab::json_adapter::IJSONAdapter&,
						 service::IAuthorizationValidatorService&,
						 service::IJSONValidatorService&,
						 service::IUserModelService&);
		virtual ~UsersPutEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		std::string m_userId;
		std::string m_requestContent;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
		service::IJSONValidatorService& m_jsonValidatorService;
		service::IUserModelService& m_userModelService;
	};

}}

