#pragma once

#include "REST/Endpoints/EntityGetAllEndpoint.h"
#include "Model/Allergy.h"
#include "Model/AllergyMgr.h"

namespace seed_cpp { namespace rest {

	class AllergiesGetAllEndpoint : public EntityGetAllEndpoint<model::Allergy, model::AllergyMgr> { using EntityGetAllEndpoint::EntityGetAllEndpoint; };

}}