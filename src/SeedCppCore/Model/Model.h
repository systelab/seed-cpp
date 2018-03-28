#pragma once

#include "Model/EntityMgr.h"

#include <memory>


namespace seed_cpp { namespace model {

	class Patient;
	class User;

	class Model
	{
	public:
		Model();
		virtual ~Model();

		EntityMgr<User>& getUserMgr() const;
		EntityMgr<Patient>& getPatientMgr() const;

	private:
		std::unique_ptr< EntityMgr<User> > m_userMgr;
		std::unique_ptr< EntityMgr<Patient> > m_patientMgr;
	};

}}
