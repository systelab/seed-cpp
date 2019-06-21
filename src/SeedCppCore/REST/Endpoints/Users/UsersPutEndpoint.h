#pragma once

#include "REST/Endpoints/EntityPutEndpoint.h"
#include "Model/User.h"
#include "Services/Model/IUserModelService.h"

namespace seed_cpp { namespace rest {

	class UsersPutEndpoint : public EntityPutEndpoint<model::User, service::IUserModelService> { using EntityPutEndpoint::EntityPutEndpoint; };

}}
