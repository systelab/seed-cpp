#pragma once

#include "IPatientModelService.h"

#include "Model/Patient.h"
#include "Model/PatientMgr.h"
#include "Services/Model/EntityModelService.h"

namespace seed_cpp { namespace service {

	class PatientModelService : public IPatientModelService,
								public EntityModelService<model::Patient, model::PatientMgr>
	{
	public:
		PatientModelService(model::PatientMgr&,
							dal::IDbDAOFactory&,
							service::IUUIDGeneratorService&,
							service::ITimeService&);

		model::PatientMgr& getEntityMgr() const override;
		const model::Patient* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const override;
		const model::Patient& addEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		const model::Patient& editEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) override;

		std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> createReadLock() override;
		std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> createWriteLock() override;
	};

}}