#include "stdafx.h"
#include "Model.h"

#include "Model/AllergyMgr.h"
#include "Model/PatientMgr.h"
#include "Model/UserMgr.h"


namespace seed_cpp { namespace model {

	Model::Model()
	{
	}

	Model::~Model() = default;

	AllergyMgr& Model::getAllergyMgr() const
	{
		return *m_allergyMgr;
	}

	UserMgr& Model::getUserMgr() const
	{
		return *m_userMgr;
	}

	PatientMgr& Model::getPatientMgr() const
	{
		return *m_patientMgr;
	}

}}

