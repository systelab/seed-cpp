#include "stdafx.h"
#include "AllergiesGetAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	AllergiesGetAllEndpoint::AllergiesGetAllEndpoint(model::AllergyMgr& allergyMgr,
											 const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityGetAllEndpoint(allergyMgr,
							  std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							  jsonAdapter)
	{
	}

}}

