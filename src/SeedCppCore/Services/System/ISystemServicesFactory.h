#pragma once

#include <memory>

namespace seed_cpp { namespace service {

	class IResourceService;
	class ITimeService;
	class IUUIDGeneratorService;

	class ISystemServicesFactory
	{
	public:
		virtual ~ISystemServicesFactory() = default;

		virtual std::unique_ptr<IResourceService> buildResourceService() const = 0;
		virtual std::unique_ptr<ITimeService> buildTimeService() const = 0;
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
	};

}}
