#pragma once

#include "IModelServicesFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class ModelServicesFactory : public IModelServicesFactory
	{
	public:
		ModelServicesFactory(Context&);
		virtual ~ModelServicesFactory();

		// Model entity services
		std::unique_ptr<IAllergyModelService> buildAllergyModelService() const;
		std::unique_ptr<IPatientModelService> buildPatientModelService() const;
		std::unique_ptr<IUserModelService> buildUserModelService() const;

		// Login services
		std::unique_ptr<systelab::rest_api_core::IUserRoleService> buildUserRoleModelService() const;

	private:
		Context& m_context;
	};

}}

