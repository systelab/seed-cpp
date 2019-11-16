#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"

#include <string>


namespace systelab {
	namespace jwt {
		class ITokenBuilderService;
	}
	namespace setting {
		class ISettingsService;
	}
}

namespace seed_cpp {
	namespace model {
		class User;
	}
	namespace service {
		class ITimeService;
		class IUserModelService;
	}
}

namespace seed_cpp { namespace rest {

	class UsersLoginPostEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		UsersLoginPostEndpoint(const service::IUserModelService&,
							   const service::ITimeService&,
							   const systelab::jwt::ITokenBuilderService&,
							   const systelab::setting::ISettingsService&);
		virtual ~UsersLoginPostEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData& requestData) override;

	private:
		struct LoginData
		{
			std::string m_login;
			std::string m_password;
		};

		std::unique_ptr<LoginData> getLoginDataFromRequestContent(const std::string&) const;
		const model::User* authenticate(const LoginData&) const;
		std::string buildJWT(const std::string& login) const;

	private:
		const service::IUserModelService& m_userModelService;
		const service::ITimeService& m_timeService;
		const systelab::jwt::ITokenBuilderService& m_jwtBuilderService;
		const systelab::setting::ISettingsService& m_settingsService;
	};

}}

