#pragma once

#include "SeedCppCore/Model/EntityMgr.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class IUserModelService
	{
	public:
		virtual ~IUserModelService() {};

		virtual model::EntityMgr<model::User>& getEntityMgr() const = 0;
		virtual const model::User* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const = 0;
		virtual const model::User& addEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual const model::User& editEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) = 0;

		virtual const model::User* getUserByLogin(const std::string&, const model::LockableEntityMgrSubject::IReadLock&) const = 0;
	};

}}

