#pragma once

#include <memory>


namespace seed_cpp { namespace service {

	class IUserModelService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() {};

		virtual std::unique_ptr<IUserModelService> buildUserModelService() const = 0;
	};

}}
