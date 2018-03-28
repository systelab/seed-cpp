#include "StdAfx.h"
#include "UserModelService.h"

#include "Model/User.h"


namespace seed_cpp { namespace service {

	UserModelService::UserModelService(model::EntityMgr<model::User>& userMgr)
		:m_userMgr(userMgr)
	{
	}
	
	UserModelService::~UserModelService()
	{
	}

	const model::User* UserModelService::getUserByLogin(const std::string& login) const
	{
		unsigned int nUsers = m_userMgr.count();
		for (unsigned int i = 0; i < nUsers; i++)
		{
			const model::User* user = m_userMgr.getEntityById(i);
			if (user->getLogin() == login)
			{
				return user;
			}
		}

		return NULL;
	}

}}

