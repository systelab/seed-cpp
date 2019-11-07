#pragma once

#include "SeedCppCore/Services/Model/IAllergyModelService.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"


namespace seed_cpp { namespace test_utility {

	class MockAllergyModelService : public service::IAllergyModelService
	{
	public:
		MockAllergyModelService();
		virtual ~MockAllergyModelService();

		MOCK_CONST_METHOD0(getEntityMgr, model::AllergyMgr&());
		MOCK_CONST_METHOD2(getEntityById, const model::Allergy*(const std::string&, const model::LockableEntityMgrSubject::IReadLock&));

		MOCK_METHOD2(addEntityProxy, const model::Allergy&(model::Allergy*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::Allergy& addEntity(std::unique_ptr<model::Allergy> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
		{
			return addEntityProxy(patient.release(), lock);
		}
	
		MOCK_METHOD2(editEntityProxy, const model::Allergy&(model::Allergy*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::Allergy& editEntity(std::unique_ptr<model::Allergy> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
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
