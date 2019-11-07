#include "stdafx.h"
#include "PatientsGetEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	PatientsGetEndpoint::PatientsGetEndpoint(model::PatientMgr& patientMgr,
											 const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityGetEndpoint(patientMgr,
						   std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
						   jsonAdapter)
	{
	}

}}

