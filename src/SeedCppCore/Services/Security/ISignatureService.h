#pragma once

#include <string>


namespace seed_cpp { namespace service {

	class ISignatureService
	{
	public:
		virtual ~ISignatureService() {};

		virtual std::string HMACSHA256(const std::string& key, const std::string& msg) const = 0;
		virtual std::string SHA256(const std::string& input) const = 0;
	};

}}

