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

		std::unique_ptr<IPatientModelService> buildPatientModelService() const;
		std::unique_ptr<IUserModelService> buildUserModelService() const;

	private:
		Context& m_context;
	};

}}

