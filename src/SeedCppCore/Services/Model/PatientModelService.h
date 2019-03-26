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
		using EntityModelService::EntityModelService;

		model::PatientMgr& getEntityMgr() const;
		const model::Patient* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const;
		const model::Patient& addEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&);
		const model::Patient& editEntity(std::unique_ptr<model::Patient>, const model::LockableEntityMgrSubject::IWriteLock&);
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&);
	};

}}