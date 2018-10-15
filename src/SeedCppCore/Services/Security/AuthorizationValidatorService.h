#pragma once

#include "IAuthorizationValidatorService.h"

#include <vector>


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace service {

	class IJWTValidatorService;
	class ITimeService;
	class IUserModelService;

	class AuthorizationValidatorService : public IAuthorizationValidatorService
	{
	public:
		AuthorizationValidatorService(const IJWTValidatorService&,
									  const IUserModelService&,
									  const ITimeService&);
		virtual ~AuthorizationValidatorService();

		bool validate(const std::string& token) const;

	private:
		bool validateIAT(const std::map<std::string, std::string>& claims) const;
		bool validateSUB(const std::map<std::string, std::string>& claims) const;

	private:
		const IJWTValidatorService& m_jwtValidatorService;
		const IUserModelService& m_userModelService;
		const ITimeService& m_timeService;
	};

}}

