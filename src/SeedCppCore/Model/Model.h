#pragma once

#include "Model/EntityMgr.h"
#include "Model/Patient.h"
#include "Model/User.h"


namespace seed_cpp { namespace model {

	class Model
	{
	public:
		Model();
		virtual ~Model();

		EntityMgr<User>& getUserMgr() const;
		EntityMgr<Patient>& getPatientMgr() const;

	private:
		std::unique_ptr<EntityMgr<User>> m_userMgr;
		std::unique_ptr<EntityMgr<Patient>> m_patientMgr;
	};

}}
