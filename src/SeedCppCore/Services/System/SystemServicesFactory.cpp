#include "stdafx.h"
#include "SystemServicesFactory.h"

#include "Context.h"
#include "Services/System/ResourceService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"


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

	std::unique_ptr<IUUIDGeneratorService> SystemServicesFactory::buildUUIDGeneratorService() const
	{
		return std::make_unique<UUIDGeneratorService>();
	}

}}
