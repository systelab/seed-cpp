#pragma once

#include <memory>


namespace systelab { namespace jwt {
	class ITokenBuilderService;
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService;
	class IBase64EncodeService;
	class IJSONValidatorService;
	class IJWTBuilderService;
	class IJWTValidatorService;
	class IPatientModelService;
	class IResourceService;
	class ISignatureService;
	class ITimeService;
	class IUserModelService;
	class IUUIDGeneratorService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() {};

		// Model services
		virtual std::unique_ptr<IPatientModelService> buildPatientModelService() const = 0;
		virtual std::unique_ptr<IUserModelService> buildUserModelService() const = 0;

		// Security services
		virtual std::unique_ptr<IAuthorizationValidatorService> buildAuthorizationValidatorService() const = 0;
		virtual std::unique_ptr<systelab::jwt::ITokenBuilderService> buildJWTTokenBuilderService() const = 0;
		virtual std::unique_ptr<systelab::jwt::ITokenParserService> buildJWTTokenParserService() const = 0;

		// Validator services
		virtual std::unique_ptr<IJSONValidatorService> buildJSONValidatorService() const = 0;

		// System services
		virtual std::unique_ptr<IResourceService> buildResourceService() const = 0;
		virtual std::unique_ptr<ITimeService> buildTimeService() const = 0;
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
	};

}}
