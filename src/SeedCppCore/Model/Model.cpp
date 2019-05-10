#include "stdafx.h"
#include "Model.h"

#include "Model/Patient.h"
#include "Model/User.h"


namespace seed_cpp { namespace model {

	Model::Model()
		:m_userMgr(std::make_unique<EntityMgr<User>>())
		,m_patientMgr(std::make_unique<EntityMgr<Patient>>())
	{
	}

	Model::Model(const Model& other)
		:m_userMgr(std::make_unique<EntityMgr<User>>(*other.m_userMgr))
		,m_patientMgr(std::make_unique<EntityMgr<Patient>>(*other.m_patientMgr))
	{
	}

	Model::~Model() = default;

	model::EntityMgr<User> &Model::getUserMgr() const
	{
		return *m_userMgr;
	}

	model::EntityMgr<Patient> &Model::getPatientMgr() const
	{
		return *m_patientMgr;
	}

	Model& Model::operator=(const Model& other)
	{
		m_userMgr = std::make_unique<EntityMgr<User>>(*other.m_userMgr);
		m_patientMgr = std::make_unique<EntityMgr<Patient>>(*other.m_patientMgr);

		return *this;
	}

}}

