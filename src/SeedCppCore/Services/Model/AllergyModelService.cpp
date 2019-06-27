#include "stdafx.h"
#include "AllergyModelService.h"

namespace seed_cpp { namespace service {

	model::AllergyMgr& AllergyModelService::getEntityMgr() const
	{
		return EntityModelService::getEntityMgr();
	}

	const model::Allergy* AllergyModelService::getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock& lock) const
	{
		return EntityModelService::getEntityById(id, lock);
	}

	const model::Allergy& AllergyModelService::addEntity(std::unique_ptr<model::Allergy> entity, const model::LockableEntityMgrSubject::IWriteLock& lock)
	{
		return EntityModelService::addEntity(std::move(entity), lock);
	}

	const model::Allergy& AllergyModelService::editEntity(std::unique_ptr<model::Allergy> entity, const model::LockableEntityMgrSubject::IWriteLock& lock)
	{
		return EntityModelService::editEntity(std::move(entity), lock);
	}

	void AllergyModelService::deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock& lock)
	{
		EntityModelService::deleteEntity(id, lock);
	}

	std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> AllergyModelService::createReadLock()
	{
		return EntityModelService::createReadLock();
	}

	std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> AllergyModelService::createWriteLock()
	{
		return EntityModelService::createWriteLock();
	}

}}