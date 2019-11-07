#include "stdafx.h"
#include "AllergiesPostEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	AllergiesPostEndpoint::AllergiesPostEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
												 service::IAllergyModelService& allergyModelService,
												 const service::IJSONValidatorService& jsonValidatorService,
												 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPostEndpoint("JSON_SCHEMA_ENDPOINT_ALLERGIES_POST", allergyModelService,
							std::bind(&dal::IJSONTranslatorsFactory::buildAllergyLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							jsonValidatorService, jsonAdapter)
	{
	}

}}
