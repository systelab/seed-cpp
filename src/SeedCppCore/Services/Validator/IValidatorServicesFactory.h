#pragma once

#include <memory>

namespace seed_cpp { namespace service {

	class IJSONValidatorService;

	class IValidatorServicesFactory
	{
	public:
		virtual ~IValidatorServicesFactory() {};

		virtual std::unique_ptr<IJSONValidatorService> buildJSONValidatorService() const = 0;
	};

}}
