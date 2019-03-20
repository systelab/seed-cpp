#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerAdapterInterface/Model/RequestHeaders.h"


namespace seed_cpp { namespace service {
	class IAuthorizationValidatorService;
	class IUserModelService;
}}

namespace seed_cpp { namespace rest {

	class UsersDeleteEndpoint : public IEndpoint
	{
	public:
		UsersDeleteEndpoint(const systelab::web_server::RequestHeaders&,
							const std::string& id,
							service::IUserModelService&,
							service::IAuthorizationValidatorService&);
		virtual ~UsersDeleteEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const std::string m_id;
		service::IUserModelService& m_userModelService;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

