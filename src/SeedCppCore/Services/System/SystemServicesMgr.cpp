#include "stdafx.h"
#include "SystemServicesMgr.h"

#include "Services/System/ISystemServicesFactory.h"
#include "Services/System/IResourceService.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"


namespace seed_cpp { namespace service {

	SystemServicesMgr::SystemServicesMgr(service::ISystemServicesFactory& factory)
		:m_factory(factory)
	{
	}
	
	SystemServicesMgr::~SystemServicesMgr() = default;

	IResourceService& SystemServicesMgr::getResourceService() const
	{
		if (!m_resourceService)
		{
			m_resourceService = m_factory.buildResourceService();
		}

		return *m_resourceService;
	}

	ITimeService& SystemServicesMgr::getTimeService() const
	{
		if (!m_timeService)
		{
			m_timeService = m_factory.buildTimeService();
		}

		return *m_timeService;
	}

	IUUIDGeneratorService& SystemServicesMgr::getUUIDGeneratorService() const
	{
		if (!m_uuidGeneratorService)
		{
			m_uuidGeneratorService = m_factory.buildUUIDGeneratorService();
		}

		return *m_uuidGeneratorService;
	}

}}

