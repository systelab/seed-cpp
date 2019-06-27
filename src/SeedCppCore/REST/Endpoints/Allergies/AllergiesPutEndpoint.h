#pragma once

#include "REST/Endpoints/EntityPutEndpoint.h"
#include "Model/Allergy.h"
#include "Services/Model/IAllergyModelService.h"

namespace seed_cpp { namespace rest {

	class AllergiesPutEndpoint : public EntityPutEndpoint<model::Allergy, service::IAllergyModelService> { using EntityPutEndpoint::EntityPutEndpoint; };

}}
