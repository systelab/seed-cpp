#pragma once

#include "IJWTBuilderService.h"


namespace seed_cpp { namespace service {

	class IBase64EncodeService;
	class ISignatureService;
	class ITimeService;

	class JWTBuilderService : public IJWTBuilderService
	{
	public:
		JWTBuilderService(const ITimeService&,
						  const IBase64EncodeService&,
						  const ISignatureService&);
		virtual ~JWTBuilderService();

		std::string buildJWT(const std::string& key) const;

	private:
		std::string buildJWTHeader() const;
		std::string buildJWTPayload() const;
		std::string buildJWTSignature(const std::string& jwtHeader, const std::string& jwtPayload) const;

	private:
		const ITimeService& m_timeService;
		const IBase64EncodeService& m_base64EncodeService;
		const ISignatureService& m_signatureService;
	};

}}

