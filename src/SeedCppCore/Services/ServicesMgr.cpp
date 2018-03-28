#include "StdAfx.h"
#include "ServicesMgr.h"

#include "Services/IServicesFactory.h"
#include "Services/IUserModelService.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(service::IServicesFactory& factory)
		:m_servicesFactory(factory)
		,m_userModelService()
	{
	}
	
	ServicesMgr::~ServicesMgr()
	{
	}

	service::IUserModelService& ServicesMgr::getUserModelService() const
	{
		if (!m_userModelService.get())
		{
			m_userModelService = m_servicesFactory.buildUserModelService();
		}

		return *m_userModelService;
	}

}}

