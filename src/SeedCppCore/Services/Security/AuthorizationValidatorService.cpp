#include "stdafx.h"
#include "AuthorizationValidatorService.h"

#include "Model/User.h"
#include "Services/Model/IUserModelService.h"
#include "Services/System/ITimeService.h"

#include "WebServerAdapterInterface/Model/RequestHeaders.h"

#include "JWTUtils/Services/ITokenParserService.h"

#include <boost/date_time/posix_time/conversion.hpp>
#include <vector>


namespace seed_cpp { namespace service {

	AuthorizationValidatorService::AuthorizationValidatorService(const IUserModelService& userModelService,
																 const ITimeService& timeService,
																 const systelab::jwt::ITokenParserService& jwtParserService)
		:m_userModelService(userModelService)
		,m_timeService(timeService)
		,m_jwtParserService(jwtParserService)
	{
	}

	AuthorizationValidatorService::~AuthorizationValidatorService() = default;

	bool AuthorizationValidatorService::validate(const systelab::web_server::RequestHeaders& headers) const
	{
		std::string authorizationToken = getAuthorizationToken(headers);
		if (authorizationToken.size() == 0)
		{
			return false;
		}

		std::string jwtSecurityKey = "SeedCppRocks!";
		std::vector< std::pair<std::string, std::string> > claims;
		if (!m_jwtParserService.validateJWT(authorizationToken, jwtSecurityKey, claims))
		{
			return false;
		}

		std::map<std::string, std::string> claimsMap;
		for (auto claim : claims)
		{
			claimsMap.insert(claim);
		}

		if (!validateIAT(claimsMap))
		{
			return false;
		}

		if (!validateSUB(claimsMap))
		{
			return false;
		}

		return true;
	}

	std::string AuthorizationValidatorService::getAuthorizationToken(const systelab::web_server::RequestHeaders& headers) const
	{
		if (!headers.hasHeader("Authorization"))
		{
			return "";
		}

		std::string authorizationHeader = headers.getHeader("Authorization");
		if (authorizationHeader.substr(0,7) != "Bearer ")
		{
			return "";
		}

		std::string authorizationToken = authorizationHeader.substr(7);
		return authorizationToken;
	}

	bool AuthorizationValidatorService::validateIAT(const std::map<std::string, std::string>& claims) const
	{
		auto it = claims.find("iat");
		if (it == claims.end())
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
		if (it == claims.end())
		{
			return false;
		}

		std::string login = it->second;
		model::EntityMgr<model::User>::SharedLock readLock(m_userModelService.getEntityMgr());
		const model::User* user = m_userModelService.getUserByLogin(login, readLock);
		if (!user)
		{
			return false;
		}

		return true;
	}

}}
