#pragma once

#include "Model/EntityMgr.h"
#include "Model/Patient.h"
#include "Model/User.h"


namespace seed_cpp { namespace model {

	class AllergyMgr;

	class Model
	{
	public:
		Model();
		virtual ~Model();

		AllergyMgr& getAllergyMgr() const;
		EntityMgr<User>& getUserMgr() const;
		EntityMgr<Patient>& getPatientMgr() const;

	private:
		std::unique_ptr<AllergyMgr> m_allergyMgr;
		std::unique_ptr<EntityMgr<User>> m_userMgr;
		std::unique_ptr<EntityMgr<Patient>> m_patientMgr;
	};

}}
