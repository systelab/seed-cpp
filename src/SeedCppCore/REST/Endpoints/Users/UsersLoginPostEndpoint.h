#pragma once

#include "REST/Endpoints/IEndpoint.h"

#include <string>


namespace seed_cpp {
	namespace model {
		class User;
	}
	namespace service {
		class IJWTBuilderService;
		class ITimeService;
		class IUserModelService;
	}
}

namespace seed_cpp { namespace rest {

	class UsersLoginPostEndpoint : public IEndpoint
	{
	public:
		UsersLoginPostEndpoint(const std::string& requestContent,
							   const service::IUserModelService&,
							   const service::IJWTBuilderService&,
							   const service::ITimeService&);
		virtual ~UsersLoginPostEndpoint();

		bool hasAccess(const std::string&);
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		struct LoginData
		{
			std::string m_login;
			std::string m_password;
		};

		std::unique_ptr<LoginData> getLoginDataFromRequestContent() const;
		const model::User* authenticate(const LoginData&) const;
		std::string buildJWT(const std::string& login) const;

	private:
		std::string m_requestContent;
		const service::IUserModelService& m_userModelService;
		const service::IJWTBuilderService& m_jwtBuilderService;
		const service::ITimeService& m_timeService;
	};

}}

