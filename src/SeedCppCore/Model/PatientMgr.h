#pragma once

#include "EntityMgr.h"
#include "Patient.h"

namespace seed_cpp { namespace model {
	class PatientMgr : public EntityMgr<Patient> { using EntityMgr::EntityMgr; };
}}