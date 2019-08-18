#pragma once

#include "REST/Endpoints/EntityGetEndpoint.h"
#include "Model/User.h"
#include "Model/UserMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace rest {

	class UsersGetEndpoint : public EntityGetEndpoint<model::User, model::UserMgr>
	{
	public:
		UsersGetEndpoint(model::UserMgr&,
						 const dal::IJSONTranslatorsFactory&,
						 const systelab::json::IJSONAdapter&);
	};

}}
