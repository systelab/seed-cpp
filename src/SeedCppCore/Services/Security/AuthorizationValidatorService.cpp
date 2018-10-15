#include "StdAfx.h"
#include "AuthorizationValidatorService.h"

#include "Services/Model/IUserModelService.h"
#include "Services/Security/IJWTValidatorService.h"
#include "Services/System/ITimeService.h"

#include <boost/date_time/posix_time/conversion.hpp>
#include <vector>


namespace seed_cpp { namespace service {

	AuthorizationValidatorService::AuthorizationValidatorService(const IJWTValidatorService& jwtValidatorService,
																 const IUserModelService& userModelService,
																 const ITimeService& timeService)
		:m_jwtValidatorService(jwtValidatorService)
		,m_userModelService(userModelService)
		,m_timeService(timeService)
	{
	}

	AuthorizationValidatorService::~AuthorizationValidatorService()
	{
	}

	bool AuthorizationValidatorService::validate(const std::string& token) const
	{
		std::map<std::string, std::string> claims;
		std::string jwtSecurityKey = "SeedCppRocks!";
		if (!m_jwtValidatorService.validateJWT(token, jwtSecurityKey, claims))
		{
			return false;
		}

		if (!validateIAT(claims))
		{
			return false;
		}

		if (!validateSUB(claims))
		{
			return false;
		}

		return true;
	}

	bool AuthorizationValidatorService::validateIAT(const std::map<std::string, std::string>& claims) const
	{
		auto it = claims.find("iat");
		if (it != claims.end())
		{
			return false;
		}

		long long iat;
		try
		{
			iat = boost::lexical_cast<long long>(it->second);
		}
		catch (std::exception&)
		{
			return false;
		}

		int maxAgeSeconds = 60 * 30; // 30'
		boost::posix_time::ptime currentTimeStamp = m_timeService.getCurrentLocalTime();
		time_t currentTimeStampSeconds = boost::posix_time::to_time_t(currentTimeStamp);
		if (std::abs(currentTimeStampSeconds - iat) > maxAgeSeconds)
		{
			return false;
		}

		return true;
	}

	bool AuthorizationValidatorService::validateSUB(const std::map<std::string, std::string>& claims) const
	{
		auto it = claims.find("sub");
		if (it != claims.end())
		{
			return false;
		}

		std::string login = it->second;
		const model::User* user = m_userModelService.getUserByLogin(login);
		if (!user)
		{
			return false;
		}

		return true;
	}

}}
