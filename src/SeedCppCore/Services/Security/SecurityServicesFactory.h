#pragma once

#include "ISecurityServicesFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class SecurityServicesFactory : public ISecurityServicesFactory
	{
	public:
		SecurityServicesFactory(Context&);
		virtual ~SecurityServicesFactory();

		std::unique_ptr<systelab::jwt::ITokenBuilderService> buildJWTTokenBuilderService() const;
		std::unique_ptr<systelab::jwt::ITokenParserService> buildJWTTokenParserService() const;

	private:
		Context& m_context;
	};

}}

