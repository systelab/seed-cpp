#include "stdafx.h"
#include "AllergiesGetEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	AllergiesGetEndpoint::AllergiesGetEndpoint(model::AllergyMgr& allergyMgr,
											   const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											   const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityGetEndpoint(allergyMgr,
						   std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   jsonAdapter)
	{
	}

}}

