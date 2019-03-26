#pragma once

#include "EntityMgr.h"
#include "Allergy.h"

namespace seed_cpp { namespace model {
	class AllergyMgr : public EntityMgr<Allergy> { using EntityMgr::EntityMgr; };
}}