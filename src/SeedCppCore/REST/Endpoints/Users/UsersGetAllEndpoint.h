#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetAllEndpoint.h"
#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"


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

