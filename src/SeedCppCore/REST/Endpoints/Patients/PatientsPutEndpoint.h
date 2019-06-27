#pragma once

#include "REST/Endpoints/EntityPutEndpoint.h"
#include "Model/Patient.h"
#include "Services/Model/IPatientModelService.h"

namespace seed_cpp { namespace rest {

	class PatientsPutEndpoint : public EntityPutEndpoint<model::Patient, service::IPatientModelService> { using EntityPutEndpoint::EntityPutEndpoint; };

}}
