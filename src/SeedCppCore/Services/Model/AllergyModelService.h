#pragma once

#include "IAllergyModelService.h"
#include "EntityModelService.h"
#include "Model/Allergy.h"
#include "Model/AllergyMgr.h"

namespace seed_cpp { namespace service {

	class AllergyModelService	: public IAllergyModelService
								, public EntityModelService<model::Allergy, model::AllergyMgr>
	{
	public:
		using EntityModelService::EntityModelService;

		model::AllergyMgr& getEntityMgr() const override;
		const model::Allergy* getEntityById(const std::string& id, const model::LockableEntityMgrSubject::IReadLock&) const override;
		const model::Allergy& addEntity(std::unique_ptr<model::Allergy>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		const model::Allergy& editEntity(std::unique_ptr<model::Allergy>, const model::LockableEntityMgrSubject::IWriteLock&) override;
		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock&) override;
	};

}}