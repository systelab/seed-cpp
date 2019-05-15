#pragma once

#include <memory>


namespace systelab { namespace jwt {
	class ITokenBuilderService;
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService;

	class ISecurityServicesFactory
	{
	public:
		virtual ~ISecurityServicesFactory() {};

		virtual std::unique_ptr<IAuthorizationValidatorService> buildAuthorizationValidatorService() const = 0;
		virtual std::unique_ptr<systelab::jwt::ITokenBuilderService> buildJWTTokenBuilderService() const = 0;
		virtual std::unique_ptr<systelab::jwt::ITokenParserService> buildJWTTokenParserService() const = 0;
	};

}}
