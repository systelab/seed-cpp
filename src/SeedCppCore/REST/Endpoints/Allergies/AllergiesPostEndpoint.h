#pragma once

#include "REST/Endpoints/EntityPostEndpoint.h"

#include "Model/Allergy.h"
#include "Services/Model/IAllergyModelService.h"

namespace seed_cpp { namespace rest {

	class AllergiesPostEndpoint : public EntityPostEndpoint<model::Allergy, service::IAllergyModelService> { using EntityPostEndpoint::EntityPostEndpoint; };

}}
