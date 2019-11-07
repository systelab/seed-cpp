#include "stdafx.h"
#include "UsersGetAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	UsersGetAllEndpoint::UsersGetAllEndpoint(model::UserMgr& userMgr,
											 const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityGetAllEndpoint(userMgr,
							  std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							  jsonAdapter)
	{
	}
}}

