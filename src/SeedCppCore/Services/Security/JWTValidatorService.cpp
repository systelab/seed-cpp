#include "StdAfx.h"
#include "JWTValidatorService.h"

#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/ISignatureService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"

#include <boost/date_time/posix_time/conversion.hpp>
#include <vector>


namespace seed_cpp { namespace service {

	JWTValidatorService::JWTValidatorService(const IBase64EncodeService& base64EncodeService,
											 const ISignatureService& signatureService,
											 const systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_base64EncodeService(base64EncodeService)
		,m_signatureService(signatureService)
		,m_jsonAdapter(jsonAdapter)
	{
	}

	JWTValidatorService::~JWTValidatorService()
	{
	}

	bool JWTValidatorService::validateJWT(const std::string& token,
										  const std::string& key,
										  std::map<std::string, std::string>& claims) const
	{
		std::vector<std::string> tokenElements = getTokenElements(token);
		if (tokenElements.size() != 3)
		{
			return false;
		}

		std::string jwtHeader = m_base64EncodeService.decodeString(tokenElements[0]);
		std::string jwtPayload = m_base64EncodeService.decodeString(tokenElements[1]);
		std::string jwtSignature = tokenElements[2];

		if (!validateSignature(jwtHeader, jwtPayload, jwtSignature, key))
		{
			return false;
		}

		claims = extractClaims(jwtPayload);

		return true;
	}

	std::vector<std::string> JWTValidatorService::getTokenElements(const std::string& token) const
	{
		std::vector<std::string> tokenElements;

		std::stringstream stream(token);
		while (stream.good())
		{
			std::string item;
			getline(stream, item, ',');
			tokenElements.push_back(item);
		}

		return tokenElements;
	}

	bool JWTValidatorService::validateSignature(const std::string& jwtHeader,
												const std::string& jwtPayload,
												const std::string& jwtSignature,
												const std::string& key) const
	{
		std::string computedJWTSignature = m_signatureService.HMACSHA256(key, jwtHeader + "." + jwtPayload);

		std::string jwtSignatureClean = jwtSignature.substr(0, jwtSignature.find_first_of("="));
		std::string computedJWTSignatureClean = computedJWTSignature.substr(0, computedJWTSignature.find_first_of("="));

		return (jwtSignatureClean == computedJWTSignatureClean);
	}

	std::map<std::string, std::string> JWTValidatorService::extractClaims(const std::string& jwtPayload) const
	{
		std::map<std::string, std::string> claims;

		auto jsonPayloadDocument = m_jsonAdapter.buildDocumentFromString(jwtPayload);
		if (!jsonPayloadDocument)
		{
			return claims;
		}

		systelab::json_adapter::IJSONValue& jsonPayloadRoot = jsonPayloadDocument->getRootValue();
		auto memberNames = jsonPayloadRoot.getObjectMemberNames();
		size_t nMembers = memberNames.size();
		for (size_t i = 0; i < nMembers; i++)
		{
			std::string claimName = memberNames[i];
			systelab::json_adapter::IJSONValue& jsonClaimValue = jsonPayloadRoot.getObjectMemberValue(claimName);
			std::string claimValue = jsonClaimValue.getString();
			claims.insert( {claimName, claimValue} );
		}

		return claims;
	}

	//bool JWTValidatorService::validateIAT(const std::string& jwtPayload,
	//									  const boost::posix_time::ptime& currentTimeStamp,
	//									  unsigned int maxAge) const
	//{
	//	auto jsonPayloadDocument = m_jsonAdapter.buildDocumentFromString(jwtPayload);
	//	if (!jsonPayloadDocument)
	//	{
	//		return false;
	//	}

	//	systelab::json_adapter::IJSONValue& jsonPayloadRoot = jsonPayloadDocument->getRootValue();
	//	if (!jsonPayloadRoot.hasObjectMember("iat"))
	//	{
	//		return false;
	//	}

	//	systelab::json_adapter::IJSONValue& jsonIATValue = jsonPayloadRoot.getObjectMemberValue("iat");
	//	if (!jsonIATValue.isInteger())
	//	{
	//		return false;
	//	}

	//	long long iat = jsonIATValue.getInteger();
	//	time_t currentTimeStampSeconds = boost::posix_time::to_time_t(currentTimeStamp);
	//	if (std::abs(currentTimeStampSeconds - iat) > maxAge)
	//	{
	//		return false;
	//	}

	//	return true;
	//}

}}