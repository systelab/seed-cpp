#include "stdafx.h"
#include "AllergiesPutEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	AllergiesPutEndpoint::AllergiesPutEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											   service::IAllergyModelService& allergyModelService,
											   const service::IJSONValidatorService& jsonValidatorService,
											   const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPutEndpoint("JSON_SCHEMA_ENDPOINT_ALLERGIES_PUT", allergyModelService,
						   std::bind(&dal::IJSONTranslatorsFactory::buildAllergyLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   jsonValidatorService, jsonAdapter)
	{
	}

}}
