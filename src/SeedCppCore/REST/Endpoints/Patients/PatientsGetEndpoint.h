#pragma once

#include "REST/Endpoints/EntityGetEndpoint.h"
#include "Model/Patient.h"
#include "Model/PatientMgr.h"

namespace seed_cpp { namespace rest {

	class PatientsGetEndpoint : public EntityGetEndpoint<model::Patient, model::PatientMgr> { using EntityGetEndpoint::EntityGetEndpoint; };

}}

