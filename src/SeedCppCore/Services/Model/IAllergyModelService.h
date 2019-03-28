#pragma once

#include "Model/LockableEntityMgrSubject.h"

namespace seed_cpp { namespace model {
	class Allergy;
	class AllergyMgr;
}}

namespace seed_cpp { namespace service {

	class IAllergyModelService
	{
	public:
		virtual ~IAllergyModelService() = default;

		virtual model::AllergyMgr& getEntityMgr() const = 0;
		virtual const model::Allergy* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const = 0;
		virtual const model::Allergy& addEntity(std::unique_ptr<model::Allergy>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual const model::Allergy& editEntity(std::unique_ptr<model::Allergy>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) = 0;

		virtual std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> createReadLock() = 0;
		virtual std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> createWriteLock() = 0;
	};

}}