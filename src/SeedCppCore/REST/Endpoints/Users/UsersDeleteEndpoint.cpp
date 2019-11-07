#include "stdafx.h"
#include "UsersDeleteEndpoint.h"


namespace seed_cpp { namespace rest {

	UsersDeleteEndpoint::UsersDeleteEndpoint(service::IUserModelService& userModelService)
		:EntityDeleteEndpoint(userModelService)
	{
	}

}}

