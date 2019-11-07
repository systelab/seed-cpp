#pragma once

#include <memory>


namespace systelab { namespace jwt {
	class ITokenBuilderService;
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class ISecurityServicesFactory
	{
	public:
		virtual ~ISecurityServicesFactory() = default;

		virtual std::unique_ptr<systelab::jwt::ITokenBuilderService> buildJWTTokenBuilderService() const = 0;
		virtual std::unique_ptr<systelab::jwt::ITokenParserService> buildJWTTokenParserService() const = 0;
	};

}}
