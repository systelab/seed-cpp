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
		~ServicesFactory();

		virtual std::unique_ptr<IUserModelService> buildUserModelService() const;

	private:
		Core& m_core;
	};

}}

