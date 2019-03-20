#pragma once

#include "IJWTBuilderService.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace service {

	class IBase64EncodeService;
	class ISignatureService;

	class JWTBuilderService : public IJWTBuilderService
	{
	public:
		JWTBuilderService(const IBase64EncodeService&,
						  const ISignatureService&,
						  const systelab::json::IJSONAdapter&);
		virtual ~JWTBuilderService();

		std::string buildJWT(const std::string& key,
							 const std::map<std::string, std::string>& claims) const;

	private:
		std::string buildJWTHeader() const;
		std::string buildJWTPayload(const std::map<std::string, std::string>& claims) const;
		std::string buildJWTSignature(const std::string& jwtHeader,
									  const std::string& jwtPayload,
									  const std::string& key) const;

	private:
		const IBase64EncodeService& m_base64EncodeService;
		const ISignatureService& m_signatureService;
		const systelab::json::IJSONAdapter& m_jsonAdapter;
	};

}}

