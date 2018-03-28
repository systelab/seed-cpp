#include "StdAfx.h"
#include "ServicesFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/UserModelService.h"


namespace seed_cpp { namespace service {

	ServicesFactory::ServicesFactory(Core& core)
		:m_core(core)
	{
	}
	
	ServicesFactory::~ServicesFactory()
	{
	}

	std::unique_ptr<IUserModelService> ServicesFactory::buildUserModelService() const
	{
		model::EntityMgr<model::User>& userMgr = m_core.getModel().getUserMgr();
		return std::unique_ptr<IUserModelService>(new UserModelService(userMgr));
	}

}}
