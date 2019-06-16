#pragma once

#include "SeedCppCore/Model/EntityMgr.h"

namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace service {

	class IPatientModelService
	{
	public:
		virtual ~IPatientModelService() = default;

		virtual model::EntityMgr<model::Patient>& getEntityMgr() const = 0;
		virtual const model::Patient* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const = 0;
		virtual const model::Patient& addEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual const model::Patient& editEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
	};

}}
