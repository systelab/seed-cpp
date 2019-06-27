#pragma once

#include "REST/Endpoints/EntityPostEndpoint.h"

#include "Model/User.h"
#include "Services/Model/IUserModelService.h"

namespace seed_cpp { namespace rest {

	class UsersPostEndpoint : public EntityPostEndpoint<model::User, service::IUserModelService> { using EntityPostEndpoint::EntityPostEndpoint; };

}}
