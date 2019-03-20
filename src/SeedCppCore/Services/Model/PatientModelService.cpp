#include "stdafx.h"
#include "PatientModelService.h"


namespace seed_cpp { namespace service {

	PatientModelService::PatientModelService(model::EntityMgr<model::Patient>& entityMgr,
											 dal::IDbDAOFactory& daoFactory,
											 service::IUUIDGeneratorService& uuidGeneratorService,
											 service::ITimeService& timeService)
		:EntityModelService(entityMgr, daoFactory, uuidGeneratorService, timeService)
	{
	}

	model::EntityMgr<model::Patient>& PatientModelService::getEntityMgr() const
	{
		return EntityModelService::getEntityMgr();
	}

	const model::Patient* PatientModelService::getEntityById(const std::string& id,
															 const model::LockableEntityMgrSubject::IReadLock& readLock) const
	{
		return EntityModelService::getEntityById(id, readLock);
	}

	const model::Patient& PatientModelService::addEntity(std::unique_ptr<model::Patient> entity,
														 const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		return EntityModelService::addEntity(std::move(entity), writeLock);
	}

	const model::Patient& PatientModelService::editEntity(std::unique_ptr<model::Patient> entity,
														  const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		return EntityModelService::editEntity(std::move(entity), writeLock);
	}

	void PatientModelService::deleteEntity(const std::string& id,
										   const model::LockableEntityMgrSubject::IWriteLock& writeLock)
	{
		EntityModelService::deleteEntity(id, writeLock);
	}

}}

