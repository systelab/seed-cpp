#pragma once

#include <string>


namespace seed_cpp { namespace service {

	class IBase64EncodeService
	{
	public:
		virtual ~IBase64EncodeService() {};

		virtual std::string encodeString(const std::string&) const = 0;
		virtual std::string decodeString(const std::string&) const = 0;
	};

}}
