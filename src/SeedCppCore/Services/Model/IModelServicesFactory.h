#pragma once

#include <memory>


namespace systelab { namespace rest_api_core {
	class IUserRoleService;
}}

namespace seed_cpp { namespace service {

	class IAllergyModelService;
	class IPatientModelService;
	class IUserModelService;

	class IModelServicesFactory
	{
	public:
		virtual ~IModelServicesFactory() = default;

		// Model entity services
		virtual std::unique_ptr<IAllergyModelService> buildAllergyModelService() const = 0;
		virtual std::unique_ptr<IPatientModelService> buildPatientModelService() const = 0;
		virtual std::unique_ptr<IUserModelService> buildUserModelService() const = 0;

		// Login services
		virtual std::unique_ptr<systelab::rest_api_core::IUserRoleService> buildUserRoleModelService() const = 0;
	};

}}
