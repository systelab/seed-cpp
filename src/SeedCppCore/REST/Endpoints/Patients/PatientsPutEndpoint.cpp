#include "stdafx.h"
#include "PatientsPutEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	PatientsPutEndpoint::PatientsPutEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 service::IPatientModelService& patientModelService,
											 const service::IJSONValidatorService& jsonValidatorService,
											 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPutEndpoint("JSON_SCHEMA_ENDPOINT_PATIENTS_PUT", patientModelService,
						   std::bind(&dal::IJSONTranslatorsFactory::buildPatientLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   jsonValidatorService, jsonAdapter)
	{
	}

}}
