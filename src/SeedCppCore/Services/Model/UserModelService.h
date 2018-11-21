#pragma once

#include "IUserModelService.h"
#include "Model/EntityMgr.h"

#include "Model/User.h"
#include "Services/Model/EntityModelService.h"
#include "Services/Model/IUserModelService.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class UserModelService : public IUserModelService,
							 public EntityModelService<model::User>
	{
	public:
		UserModelService(model::EntityMgr<model::User>&,
						 dal::IDbDAOFactory&,
						 service::IUUIDGeneratorService&,
						 service::ITimeService&);
		virtual ~UserModelService() = default;

		model::EntityMgr<model::User>& getEntityMgr() const;
		const model::User* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const;
		const model::User& addEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&);
		const model::User& editEntity(std::unique_ptr<model::User>, const model::LockableEntityMgrSubject::IWriteLock&);
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&);

		const model::User* getUserByLogin(const std::string&, const model::LockableEntityMgrSubject::IReadLock&) const;

	private:
		model::EntityMgr<model::User>& m_userMgr;
	};

}}

