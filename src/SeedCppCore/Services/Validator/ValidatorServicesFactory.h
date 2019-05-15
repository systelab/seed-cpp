#pragma once

#include "IValidatorServicesFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class ValidatorServicesFactory : public IValidatorServicesFactory
	{
	public:
		ValidatorServicesFactory(Context&);
		virtual ~ValidatorServicesFactory();

		std::unique_ptr<IJSONValidatorService> buildJSONValidatorService() const;

	private:
		Context& m_context;
	};

}}

