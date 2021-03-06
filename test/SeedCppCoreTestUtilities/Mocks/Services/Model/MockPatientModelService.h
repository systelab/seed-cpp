#pragma once

#include "SeedCppCore/Services/Model/IPatientModelService.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"


namespace seed_cpp { namespace test_utility {

	class MockPatientModelService : public service::IPatientModelService
	{
	public:
		MockPatientModelService();
		virtual ~MockPatientModelService();

		MOCK_CONST_METHOD0(getEntityMgr, model::PatientMgr&());
		MOCK_CONST_METHOD2(getEntityById, const model::Patient*(const std::string&, const model::LockableEntityMgrSubject::IReadLock&));

		MOCK_METHOD2(addEntityProxy, const model::Patient&(model::Patient*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::Patient& addEntity(std::unique_ptr<model::Patient> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
		{
			return addEntityProxy(patient.release(), lock);
		}
	
		MOCK_METHOD2(editEntityProxy, const model::Patient&(model::Patient*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::Patient& editEntity(std::unique_ptr<model::Patient> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
		{
			return editEntityProxy(patient.release(), lock);
		}

		MOCK_METHOD2(deleteEntity, void(const std::string&, const model::LockableEntityMgrSubject::IWriteLock&));

		MOCK_METHOD0(createReadLockProxy, model::LockableEntityMgrSubject::IReadLock*());
		std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> createReadLock() override
		{
			return std::unique_ptr<model::LockableEntityMgrSubject::IReadLock>(createReadLockProxy());
		}

		MOCK_METHOD0(createWriteLockProxy, model::LockableEntityMgrSubject::IWriteLock*());
		std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> createWriteLock() override
		{
			return std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock>(createWriteLockProxy());
		}
	};

}}
