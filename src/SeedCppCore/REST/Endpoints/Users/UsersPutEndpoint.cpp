#include "stdafx.h"
#include "UsersPutEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	UsersPutEndpoint::UsersPutEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
									   service::IUserModelService& userModelService,
									   const service::IJSONValidatorService& jsonValidatorService,
									   const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPutEndpoint("JSON_SCHEMA_ENDPOINT_USERS_PUT", userModelService,
						   std::bind(&dal::IJSONTranslatorsFactory::buildUserLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   jsonValidatorService, jsonAdapter)
	{
	}

}}
