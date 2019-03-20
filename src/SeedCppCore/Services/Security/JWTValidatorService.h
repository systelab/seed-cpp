#pragma once

#include "IJWTValidatorService.h"

#include <vector>


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace service {

	class IBase64EncodeService;
	class ISignatureService;

	class JWTValidatorService : public IJWTValidatorService
	{
	public:
		JWTValidatorService(const IBase64EncodeService&,
							const ISignatureService&,
							const systelab::json::IJSONAdapter&);
		virtual ~JWTValidatorService();

		bool validateJWT(const std::string& token, const std::string& key,
						 std::map<std::string, std::string>& claims) const;

	private:
		std::vector<std::string> getTokenElements(const std::string& token) const;
		bool validateSignature(const std::string& jwtHeader, const std::string& jwtPayload,
							   const std::string& jwtSignature, const std::string& key) const;
		std::map<std::string, std::string> extractClaims(const std::string& jwtPayload) const;

	private:
		const IBase64EncodeService& m_base64EncodeService;
		const ISignatureService& m_signatureService;
		const systelab::json::IJSONAdapter& m_jsonAdapter;
	};

}}

