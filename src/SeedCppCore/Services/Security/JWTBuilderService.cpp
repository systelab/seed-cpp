#include "StdAfx.h"
#include "JWTBuilderService.h"

#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/ISignatureService.h"
#include "Services/System/ITimeService.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <boost/throw_exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/algorithm/string.hpp>

#include <vector>


namespace seed_cpp { namespace service {

	JWTBuilderService::JWTBuilderService(const ITimeService& timeService,
										 const IBase64EncodeService& base64EncodeService,
										 const ISignatureService& signatureService)
		:m_timeService(timeService)
		,m_base64EncodeService(base64EncodeService)
		,m_signatureService(signatureService)
	{
	}

	JWTBuilderService::~JWTBuilderService()
	{
	}

	std::string JWTBuilderService::buildJWT(const std::string& key) const
	{
		std::string jwtHeader = buildJWTHeader();
		std::string jwtPayload = buildJWTPayload();
		std::string jwtSignature = buildJWTSignature(jwtHeader, jwtPayload);
		std::string jwt = jwtHeader + "." + jwtPayload + "." + jwtSignature;

		return jwt;
	}

	std::string JWTBuilderService::buildJWTHeader() const
	{
		rapidjson::Document document;
		document.SetObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		document.AddMember("alg", "HS256", allocator);
		document.AddMember("typ", "JWT", allocator);

		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return m_base64EncodeService.encodeString(buffer.GetString());
	}

	std::string JWTBuilderService::buildJWTPayload() const
	{
		rapidjson::Document document;
		document.SetObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		document.AddMember("iat", getCurrentTimestamp(), allocator);

		rapidjson::StringBuffer buffer;

		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return m_base64EncodeService.encodeString(buffer.GetString());
	}

	std::string JWTBuilderService::buildJWTSignature(const std::string& jwtHeader, const std::string& jwtPayload) const
	{
		rapidjson::Document document;
		document.SetObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
		document.AddMember("iat", getCurrentTimestamp(), allocator);

		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return m_base64EncodeService.encodeString(buffer.GetString());
	}

	time_t JWTBuilderService::getCurrentTimestamp() const
	{
		time_t now;
		time(&now);

		return now;
	}

}}