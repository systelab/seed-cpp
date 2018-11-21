#pragma once

#include "Model/Address.h"
#include "Model/Patient.h"
#include "Services/Model/EntityModelService.h"
#include "Services/Model/IPatientModelService.h"


namespace seed_cpp { namespace service {

	class PatientModelService : public IPatientModelService,
								public EntityModelService<model::Patient>
	{
	public:
		PatientModelService(model::EntityMgr<model::Patient>&,
							dal::IDbDAOFactory&,
							service::IUUIDGeneratorService&,
							service::ITimeService&);
		virtual ~PatientModelService() = default;

		model::EntityMgr<model::Patient>& getEntityMgr() const;
		const model::Patient* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const;
		const model::Patient& addEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&);
		const model::Patient& editEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&);
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&);
	};

}}