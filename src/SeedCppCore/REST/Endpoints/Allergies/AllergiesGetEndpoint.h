#pragma once

#include "REST/Endpoints/EntityGetEndpoint.h"
#include "Model/Allergy.h"
#include "Model/AllergyMgr.h"

namespace seed_cpp { namespace rest {

	class AllergiesGetEndpoint : public EntityGetEndpoint<model::Allergy, model::AllergyMgr> { using EntityGetEndpoint::EntityGetEndpoint; };

}}