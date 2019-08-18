#include "stdafx.h"
#include "UsersPostEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	UsersPostEndpoint::UsersPostEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
										 service::IUserModelService& userModelService,
										 const service::IJSONValidatorService& jsonValidatorService,
										 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPostEndpoint("JSON_SCHEMA_ENDPOINT_USERS_POST", userModelService,
							std::bind(&dal::IJSONTranslatorsFactory::buildUserLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							jsonValidatorService, jsonAdapter)
	{
	}

}}
