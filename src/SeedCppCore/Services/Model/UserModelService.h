#pragma once

#include "IUserModelService.h"

#include "Model/User.h"
#include "Model/UserMgr.h"
#include "Services/Model/EntityModelService.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class UserModelService : public IUserModelService,
							 public EntityModelService<model::User, model::UserMgr>
	{
	public:
		UserModelService(model::UserMgr&,
						 dal::IDbDAOFactory&,
						 service::IUUIDGeneratorService&,
						 service::ITimeService&);

		model::UserMgr& getEntityMgr() const override;
		const model::User* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const override;
		const model::User& addEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		const model::User& editEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) override;

		std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> createReadLock() override;
		std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> createWriteLock() override;

		const model::User* getUserByLogin(const std::string&, const model::LockableEntityMgrSubject::IReadLock&) const override;
	};

}}

