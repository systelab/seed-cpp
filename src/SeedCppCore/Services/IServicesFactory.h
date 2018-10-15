#pragma once

#include <memory>


namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService;
	class IBase64EncodeService;
	class IJWTBuilderService;
	class IJWTValidatorService;
	class ISignatureService;
	class ITimeService;
	class IUserModelService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() {};

		// Model services
		virtual std::unique_ptr<IUserModelService> buildUserModelService() const = 0;

		// Security services
		virtual std::unique_ptr<IAuthorizationValidatorService> buildAuthorizationValidatorService() const = 0;
		virtual std::unique_ptr<IJWTBuilderService> buildJWTBuilderService() const = 0;
		virtual std::unique_ptr<IJWTValidatorService> buildJWTValidatorService() const = 0;
		virtual std::unique_ptr<ISignatureService> buildSignatureService() const = 0;
		virtual std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const = 0;

		// System services
		virtual std::unique_ptr<ITimeService> buildTimeService() const = 0;
	};

}}
