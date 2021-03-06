#pragma once

#include "SeedCppCore/Services/Model/IUserModelService.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"


namespace seed_cpp { namespace test_utility {

	class MockUserModelService : public service::IUserModelService
	{
	public:
		MockUserModelService();
		virtual ~MockUserModelService();

		MOCK_CONST_METHOD0(getEntityMgr, model::UserMgr&());
		MOCK_CONST_METHOD2(getEntityById, const model::User*(const std::string&, const model::LockableEntityMgrSubject::IReadLock&));
		MOCK_CONST_METHOD2(getUserByLogin, const model::User*(const std::string&, const model::LockableEntityMgrSubject::IReadLock&));

		MOCK_METHOD2(addEntityProxy, const model::User&(model::User*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::User& addEntity(std::unique_ptr<model::User> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
		{
			return addEntityProxy(patient.release(), lock);
		}
	
		MOCK_METHOD2(editEntityProxy, const model::User&(model::User*, const model::LockableEntityMgrSubject::IWriteLock&));
		const model::User& editEntity(std::unique_ptr<model::User> patient, const model::LockableEntityMgrSubject::IWriteLock& lock) override
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
