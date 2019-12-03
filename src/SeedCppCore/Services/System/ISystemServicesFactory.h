#pragma once

#include <memory>


namespace systelab {
	namespace rest_api_core {
		class IEpochTimeService;
	}
	namespace setting {
		class ISettingsService;
	}
}

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
		virtual std::unique_ptr<systelab::rest_api_core::IEpochTimeService> buildEpochTimeService() const = 0;
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
		virtual std::unique_ptr<systelab::setting::ISettingsService> buildSettingsService() const = 0;
	};

}}
