#include "stdafx.h"
#include "Model.h"

#include "Model/AllergyMgr.h"
#include "Model/Patient.h"
#include "Model/User.h"


namespace seed_cpp { namespace model {

	Model::Model()
	{
	}

	Model::~Model() = default;

	AllergyMgr& Model::getAllergyMgr() const
	{
		return *m_allergyMgr;
	}

	EntityMgr<User>& Model::getUserMgr() const
	{
		return *m_userMgr;
	}

	EntityMgr<Patient>& Model::getPatientMgr() const
	{
		return *m_patientMgr;
	}

}}

