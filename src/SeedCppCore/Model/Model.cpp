#include "stdafx.h"
#include "Model.h"

#include "Model/AllergyMgr.h"
#include "Model/PatientMgr.h"
#include "Model/UserMgr.h"


namespace seed_cpp { namespace model {

	Model::Model()
		:m_allergyMgr(std::make_unique<AllergyMgr>())
		,m_patientMgr(std::make_unique<PatientMgr>())
		,m_userMgr(std::make_unique<UserMgr>())
	{
	}

	Model::Model(const Model& other)
		:m_allergyMgr(std::make_unique<AllergyMgr>(*other.m_allergyMgr))
		,m_patientMgr(std::make_unique<PatientMgr>(*other.m_patientMgr))
		,m_userMgr(std::make_unique<UserMgr>(*other.m_userMgr))
	{
	}

	Model::~Model() = default;

	AllergyMgr& Model::getAllergyMgr() const
	{
		return *m_allergyMgr;
	}

	PatientMgr& Model::getPatientMgr() const
	{
		return *m_patientMgr;
	}

	UserMgr& Model::getUserMgr() const
	{
		return *m_userMgr;
	}

	Model& Model::operator=(const Model& other)
	{
		m_allergyMgr = std::make_unique<AllergyMgr>(*other.m_allergyMgr);
		m_patientMgr = std::make_unique<PatientMgr>(*other.m_patientMgr);
		m_userMgr = std::make_unique<UserMgr>(*other.m_userMgr);

		return *this;
	}

}}

