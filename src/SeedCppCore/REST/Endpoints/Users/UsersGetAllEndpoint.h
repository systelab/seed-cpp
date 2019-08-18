#pragma once

#include "REST/Endpoints/EntityGetAllEndpoint.h"
#include "Model/User.h"
#include "Model/UserMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace seed_cpp { namespace rest {

	class UsersGetAllEndpoint : public EntityGetAllEndpoint<model::User, model::UserMgr>
	{
	public:
		UsersGetAllEndpoint(model::UserMgr&,
							const dal::IJSONTranslatorsFactory&,
							const systelab::json::IJSONAdapter&);
	};

}}

