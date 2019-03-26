#include "stdafx.h"
#include "UserModelService.h"

#include "Model/User.h"


namespace seed_cpp { namespace service {

	
	model::UserMgr& UserModelService::getEntityMgr() const
	{
		return EntityModelService::getEntityMgr();
	}

	const model::User* UserModelService::getEntityById(const std::string& id,
													   const model::LockableEntityMgrSubject::IReadLock& readLock) const
	{
		return EntityModelService::getEntityById(id, readLock);
	}

	const model::User& UserModelService::addEntity(std::unique_ptr<model::User> entity,
												   const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		return EntityModelService::addEntity(std::move(entity), writeLock);
	}

	const model::User& UserModelService::editEntity(std::unique_ptr<model::User> entity,
													const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		return EntityModelService::editEntity(std::move(entity), writeLock);
	}

	void UserModelService::deleteEntity(const std::string& id,
										const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		EntityModelService::deleteEntity(id, writeLock);
	}

	const model::User* UserModelService::getUserByLogin(const std::string& login,
														const model::LockableEntityMgrSubject::IReadLock& readLock) const
	{
		unsigned int nUsers = m_entityMgr.count();
		for (unsigned int i = 0; i < nUsers; i++)
		{
			const model::User* user = m_entityMgr.getEntity(i, readLock);
			if (user->getLogin() == login)
			{
				return user;
			}
		}

		return NULL;
	}

}}

