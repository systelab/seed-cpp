#pragma once

#include "SeedCppCore/Model/EntityMgr.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace model {

	class Model
	{
	public:
		Model();
		Model(const Model&);
		virtual ~Model();

		EntityMgr<User>& getUserMgr() const;
		EntityMgr<Patient>& getPatientMgr() const;

		Model& operator= (const Model&);

	private:
		std::unique_ptr<EntityMgr<User>> m_userMgr;
		std::unique_ptr<EntityMgr<Patient>> m_patientMgr;
	};

}}
