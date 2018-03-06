#include "StdAfx.h"
#include "Model.h"

#include "Model/Patient.h"


namespace seed_cpp { namespace model {

	Model::Model()
		:m_patientMgr(new EntityMgr<Patient>())
	{
	}

	Model::~Model()
	{
	}

	model::EntityMgr<Patient>& Model::getPatientMgr() const
	{
		return *m_patientMgr;
	}

}}
