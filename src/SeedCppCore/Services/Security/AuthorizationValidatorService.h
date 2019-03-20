#pragma once

#include "IAuthorizationValidatorService.h"

#include <map>
#include <vector>


namespace systelab { namespace jwt {
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class ITimeService;
	class IUserModelService;

	class AuthorizationValidatorService : public IAuthorizationValidatorService
	{
	public:
		AuthorizationValidatorService(const IUserModelService&,
									  const ITimeService&,
									  const systelab::jwt::ITokenParserService&);
		virtual ~AuthorizationValidatorService();

		bool validate(const systelab::web_server::RequestHeaders&) const;

	private:
		std::string getAuthorizationToken(const systelab::web_server::RequestHeaders&) const;
		bool validateIAT(const std::map<std::string, std::string>& claims) const;
		bool validateSUB(const std::map<std::string, std::string>& claims) const;

	private:
		const IUserModelService& m_userModelService;
		const ITimeService& m_timeService;
		const systelab::jwt::ITokenParserService& m_jwtParserService;
	};

}}

