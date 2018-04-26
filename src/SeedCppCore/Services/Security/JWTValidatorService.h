#pragma once

#include "IJWTValidatorService.h"

#include <vector>


namespace systelab { namespace json_adapter {
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
							const systelab::json_adapter::IJSONAdapter&);
		virtual ~JWTValidatorService();

		bool validateJWT(const std::string& token, const std::string& key,
						 const boost::posix_time::ptime& currentTimeStamp,
						 unsigned int maxAge) const;

	private:
		std::vector<std::string> getTokenElements(const std::string& token) const;
		bool validateIAT(const std::string& jwtPayload,
						 const boost::posix_time::ptime& currentTimeStamp, unsigned int maxAge) const;
		bool validateSignature(const std::string& jwtHeader, const std::string& jwtPayload,
							   const std::string& jwtSignature, const std::string& key) const;

	private:
		const IBase64EncodeService& m_base64EncodeService;
		const ISignatureService& m_signatureService;
		const systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
	};

}}

