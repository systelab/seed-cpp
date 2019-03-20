#pragma once

#include "IServicesFactory.h"


namespace seed_cpp {
	class Core;
}

namespace seed_cpp { namespace service {

	class ServicesFactory : public IServicesFactory
	{
	public:
		ServicesFactory(Core&);
		virtual ~ServicesFactory();

		// Model services
		std::unique_ptr<IPatientModelService> buildPatientModelService() const;
		std::unique_ptr<IUserModelService> buildUserModelService() const;

		// Security services
		std::unique_ptr<IAuthorizationValidatorService> buildAuthorizationValidatorService() const;
		std::unique_ptr<systelab::jwt::ITokenBuilderService> buildJWTTokenBuilderService() const;
		std::unique_ptr<systelab::jwt::ITokenParserService> buildJWTTokenParserService() const;
		std::unique_ptr<ISignatureService> buildSignatureService() const;
		std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const;

		// Validator services
		std::unique_ptr<IJSONValidatorService> buildJSONValidatorService() const;

		// System services
		std::unique_ptr<IResourceService> buildResourceService() const;
		std::unique_ptr<ITimeService> buildTimeService() const;
		std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const;

	private:
		Core& m_core;
	};

}}

