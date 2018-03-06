#pragma once

#include "Model/EntityMgr.h"

#include <memory>


namespace seed_cpp { namespace model {

	class Patient;

	class Model
	{
	public:
		Model();
		virtual ~Model();

		EntityMgr<Patient>& getPatientMgr() const;

	private:
		std::unique_ptr< EntityMgr<Patient> > m_patientMgr;
	};

}}
