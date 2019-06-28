#pragma once

#include "REST/Endpoints/EntityGetEndpoint.h"
#include "Model/User.h"
#include "Model/UserMgr.h"

namespace seed_cpp { namespace rest {

	class UsersGetEndpoint : public EntityGetEndpoint<model::User, model::UserMgr> { using EntityGetEndpoint::EntityGetEndpoint; };

}}

