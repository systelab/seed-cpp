#include "StdAfx.h"
#include "SignatureService.h"

#include "Services/Security/IBase64EncodeService.h"

#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/err.h>


namespace seed_cpp { namespace service {

	SignatureService::SignatureService(const IBase64EncodeService& base64EncodeService)
		:m_base64EncodeService(base64EncodeService)
	{
	}

	SignatureService::~SignatureService()
	{
	}

	std::string SignatureService::HMACSHA256(const std::string& key, const std::string& msg) const
	{
		unsigned int len = 32;
		unsigned char hash[32];

		HMAC_CTX hmac;
		HMAC_CTX_init(&hmac);
		HMAC_Init_ex(&hmac, &key[0], (int) key.length(), EVP_sha256(), NULL);
		HMAC_Update(&hmac, ( unsigned char* )&msg[0], msg.length());
		HMAC_Final(&hmac, hash, &len);
		HMAC_CTX_cleanup(&hmac);

		std::stringstream ss;
		ss << std::setfill('0');

		for (unsigned int i = 0; i < len; i++)
		{
			ss  << hash[i];
		}

		return m_base64EncodeService.encodeString(ss.str());
	}

	std::string SignatureService::SHA256(const std::string& input) const
	{
		EVP_MD_CTX ctx;

		unsigned int len;

		unsigned char hash[EVP_MAX_MD_SIZE];

		EVP_DigestInit(&ctx, EVP_sha256());
		EVP_DigestUpdate(&ctx, ( unsigned char* )&input[0], input.length());
		EVP_DigestFinal(&ctx, hash, &len);

		std::stringstream ss;
		ss << std::setfill('0');

		for (unsigned int i = 0; i < len; i++)
		{
			ss << std::setw(2) << std::hex << (int)hash[i];
		}

		return ss.str();
	}

}}