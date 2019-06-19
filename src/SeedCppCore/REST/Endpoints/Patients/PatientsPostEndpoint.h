#pragma once

#include "REST/Endpoints/EntityPostEndpoint.h"

#include "Model/Patient.h"
#include "Services/Model/IPatientModelService.h"

namespace seed_cpp { namespace rest {

	class PatientsPostEndpoint : public EntityPostEndpoint<model::Patient, service::IPatientModelService> { using EntityPostEndpoint::EntityPostEndpoint; };

}}
