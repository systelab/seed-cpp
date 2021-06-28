#include "stdafx.h"
#include "SystemServicesFactory.h"

#include "Context.h"
#include "Services/System/ResourceService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"

#include "JSONSettings/SettingsService.h"
#include "RESTAPICore/RouteAccess/EpochTimeService.h"

#include "TimeAdapter/TimeAdapter.h"


namespace seed_cpp { namespace service {

	SystemServicesFactory::SystemServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	SystemServicesFactory::~SystemServicesFactory() = default;

	std::unique_ptr<IResourceService> SystemServicesFactory::buildResourceService() const
	{
		return std::make_unique<ResourceService>();
	}

	std::unique_ptr<ITimeService> SystemServicesFactory::buildTimeService() const
	{
		return std::make_unique<TimeService>();
	}

	std::unique_ptr<systelab::rest_api_core::IEpochTimeService> SystemServicesFactory::buildEpochTimeService() const
	{
		systelab::time::TimeAdapter TimeAdapter;

		return std::make_unique<systelab::rest_api_core::EpochTimeService>(TimeAdapter);
	}

	std::unique_ptr<IUUIDGeneratorService> SystemServicesFactory::buildUUIDGeneratorService() const
	{
		return std::make_unique<UUIDGeneratorService>();
	}

	std::unique_ptr<systelab::setting::ISettingsService> SystemServicesFactory::buildSettingsService() const
	{
		return std::make_unique<systelab::setting::SettingsService>();
	}

}}
