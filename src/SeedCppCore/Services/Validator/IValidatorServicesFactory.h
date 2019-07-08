#pragma once

#include <memory>

namespace seed_cpp { namespace service {

	class IJSONValidatorService;

	class IValidatorServicesFactory
	{
	public:
		virtual ~IValidatorServicesFactory() = default;

		virtual std::unique_ptr<IJSONValidatorService> buildJSONValidatorService() const = 0;
	};

}}
