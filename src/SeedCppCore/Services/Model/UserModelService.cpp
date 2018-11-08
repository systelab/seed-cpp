#include "StdAfx.h"
#include "UserModelService.h"

#include "Model/User.h"


namespace seed_cpp { namespace service {

	UserModelService::UserModelService(model::EntityMgr<model::User>& userMgr,
									   dal::IDbDAOFactory& daoFactory,
									   service::IUUIDGeneratorService& uuidGeneratorService,
									   service::ITimeService& timeService)
		:EntityModelService(userMgr, daoFactory, uuidGeneratorService, timeService)
		,m_userMgr(userMgr)
	{
	}
	
	model::EntityMgr<model::User>& UserModelService::getEntityMgr() const
	{
		return EntityModelService::getEntityMgr();
	}

	const model::User* UserModelService::getEntityById(const std::string& id) const
	{
		return EntityModelService::getEntityById(id);
	}

	const model::User& UserModelService::addEntity(std::unique_ptr<model::User> entity)
	{
		return EntityModelService::addEntity(std::move(entity));
	}

	const model::User& UserModelService::editEntity(std::unique_ptr<model::User> entity)
	{
		return EntityModelService::editEntity(std::move(entity));
	}

	void UserModelService::deleteEntity(const std::string& id)
	{
		EntityModelService::deleteEntity(id);
	}

	const model::User* UserModelService::getUserByLogin(const std::string& login) const
	{
		unsigned int nUsers = m_userMgr.count();
		for (unsigned int i = 0; i < nUsers; i++)
		{
			const model::User* user = m_userMgr.getEntity(i);
			if (user->getLogin() == login)
			{
				return user;
			}
		}

		return NULL;
	}

}}

