#include "stdafx.h"
#include "PatientsPostEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	PatientsPostEndpoint::PatientsPostEndpoint(const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											   service::IPatientModelService& patientModelService,
											   const service::IJSONValidatorService& jsonValidatorService,
											   const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityPostEndpoint("JSON_SCHEMA_ENDPOINT_PATIENTS_POST", patientModelService,
							std::bind(&dal::IJSONTranslatorsFactory::buildPatientLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							jsonValidatorService, jsonAdapter)
	{
	}

}}
