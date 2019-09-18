#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetEndpoint.h"
#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"


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
