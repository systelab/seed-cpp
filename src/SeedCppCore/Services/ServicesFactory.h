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
		std::unique_ptr<IUserModelService> buildUserModelService() const;

		// Security services
		std::unique_ptr<IJWTBuilderService> buildJWTBuilderService() const;
		std::unique_ptr<IJWTValidatorService> buildJWTValidatorService() const;
		std::unique_ptr<ISignatureService> buildSignatureService() const;
		std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const;

	private:
		Core& m_core;
	};

}}

