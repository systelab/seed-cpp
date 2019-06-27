#include "stdafx.h"
#include "ModelBuilder.h"

#include "SeedCppCore/Model/AllergyMgr.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/Model/UserMgr.h"


namespace seed_cpp { namespace test_utility {

	ModelBuilder::ModelBuilder()
		:m_model()
	{
	}

	ModelBuilder::~ModelBuilder() = default;

	ModelBuilder& ModelBuilder::setAllergies(const std::vector<model::Allergy>& allergies)
	{
		auto& allergyMgr = m_model.getAllergyMgr();
		model::AllergyMgr::UniqueLock writeLock(allergyMgr);
		for (auto& allergy : allergies)
		{
			allergyMgr.addEntity(std::make_unique<model::Allergy>(allergy), writeLock);
		}

		return *this;
	}

	ModelBuilder& ModelBuilder::setPatients(const std::vector<model::Patient>& patients)
	{
		auto& patientMgr = m_model.getPatientMgr();
		model::PatientMgr::UniqueLock writeLock(patientMgr);
		for (auto& patient : patients)
		{
			patientMgr.addEntity(std::make_unique<model::Patient>(patient), writeLock);
		}

		return *this;
	}

	ModelBuilder& ModelBuilder::setUsers(const std::vector<model::User>& users)
	{
		auto& userMgr = m_model.getUserMgr();
		model::UserMgr::UniqueLock writeLock(userMgr);
		for (auto& user : users)
		{
			userMgr.addEntity(std::make_unique<model::User>(user), writeLock);
		}

		return *this;
	}

	model::Model ModelBuilder::getEntity() const
	{
		return m_model;
	}

}}
