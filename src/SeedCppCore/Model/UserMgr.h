#pragma once

#include "EntityMgr.h"
#include "User.h"

namespace seed_cpp { namespace model {
	class UserMgr : public EntityMgr<User> { using EntityMgr::EntityMgr; };
}}