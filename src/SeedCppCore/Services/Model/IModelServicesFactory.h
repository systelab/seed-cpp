#pragma once

#include <memory>

namespace seed_cpp { namespace service {

	class IAllergyModelService;
	class IPatientModelService;
	class IUserModelService;

	class IModelServicesFactory
	{
	public:
		virtual ~IModelServicesFactory() = default;

		virtual std::unique_ptr<IAllergyModelService> buildAllergyModelService() const = 0;
		virtual std::unique_ptr<IPatientModelService> buildPatientModelService() const = 0;
		virtual std::unique_ptr<IUserModelService> buildUserModelService() const = 0;
	};

}}
