#pragma once

#include "REST/Endpoints/EntityGetAllEndpoint.h"
#include "Model/User.h"
#include "Model/UserMgr.h"

namespace seed_cpp { namespace rest {

	class UsersGetAllEndpoint : public EntityGetAllEndpoint<model::User, model::UserMgr> { using EntityGetAllEndpoint::EntityGetAllEndpoint; };

}}

