#pragma once

#include "SeedCppCore/REST/Endpoints/EntityDeleteEndpoint.h"
#include "SeedCppCore/Services/Model/IUserModelService.h"


namespace seed_cpp { namespace rest {

	class UsersDeleteEndpoint : public EntityDeleteEndpoint<service::IUserModelService>
	{
	public:
		UsersDeleteEndpoint(service::IUserModelService&);
	};

}}

