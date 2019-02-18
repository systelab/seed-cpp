#include "JWTBuilderService.h"

#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/ISignatureService.h"

#include "IJSONAdapter.h"
#include "IJSONDocument.h"
#include "IJSONValue.h"

#include <boost/date_time/posix_time/conversion.hpp>
#include <vector>


namespace seed_cpp { namespace service {

	JWTBuilderService::JWTBuilderService(const IBase64EncodeService& base64EncodeService,
										 const ISignatureService& signatureService,
										 const systelab::json_adapter::IJSONAdapter& jsonAdapter)
		:m_base64EncodeService(base64EncodeService)
		,m_signatureService(signatureService)
		,m_jsonAdapter(jsonAdapter)
	{
	}

	JWTBuilderService::~JWTBuilderService()
	{
	}

	std::string JWTBuilderService::buildJWT(const std::string& key,
											const std::map<std::string, std::string>& claims) const
	{
		std::string jwtHeader = buildJWTHeader();
		std::string jwtPayload = buildJWTPayload(claims);
		std::string jwtSignature = buildJWTSignature(jwtHeader, jwtPayload, key);
		std::string jwt = jwtHeader + "." + jwtPayload + "." + jwtSignature;

		return jwt;
	}

	std::string JWTBuilderService::buildJWTHeader() const
	{
		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();
		systelab::json_adapter::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(systelab::json_adapter::OBJECT_TYPE);
		jsonRoot.addMember("alg", "HS256");
		jsonRoot.addMember("typ", "JWT");
		std::string jwtHeader = jsonDocument->serialize();

		return m_base64EncodeService.encodeString(jwtHeader);
	}

	std::string JWTBuilderService::buildJWTPayload(const std::map<std::string, std::string>& claims) const
	{
		auto jsonDocument = m_jsonAdapter.buildEmptyDocument();

		systelab::json_adapter::IJSONValue& jsonRoot = jsonDocument->getRootValue();
		jsonRoot.setType(systelab::json_adapter::OBJECT_TYPE);
		for (auto claim : claims)
		{
			jsonRoot.addMember(claim.first, claim.second);
		}

		std::string jwtPayload = jsonDocument->serialize();

		return m_base64EncodeService.encodeString(jwtPayload);
	}

	std::string JWTBuilderService::buildJWTSignature(const std::string& jwtHeader,
													 const std::string& jwtPayload,
													 const std::string& key) const
	{
		std::stringstream stream;
		stream << jwtHeader << "." << jwtPayload;
		std::string messageToSign = stream.str();

		return m_signatureService.HMACSHA256(key, messageToSign);
	}

}}
