#include "stdafx.h"
#include "ModelBuilder.h"


namespace seed_cpp { namespace test_utility {

	ModelBuilder::ModelBuilder()
		:m_model()
	{
	}

	ModelBuilder::~ModelBuilder() = default;

	ModelBuilder& ModelBuilder::setUsers(const std::vector<model::User>& users)
	{
		auto userMgr = m_model.getUserMgr();
		model::EntityMgr<model::User>::UniqueLock writeLock(userMgr);
		for (auto& user : users)
		{
			userMgr.addEntity(std::make_unique<model::User>(user), writeLock);
		}

		return *this;
	}

	ModelBuilder& ModelBuilder::setPatients(const std::vector<model::Patient>& patients)
	{
		auto patientMgr = m_model.getPatientMgr();
		model::EntityMgr<model::Patient>::UniqueLock writeLock(patientMgr);
		for (auto& patient : patients)
		{
			patientMgr.addEntity(std::make_unique<model::Patient>(patient), writeLock);
		}

		return *this;
	}

	model::Model ModelBuilder::getEntity() const
	{
		return m_model;
	}

}}
