#include "stdafx.h"
#include "PatientsGetAllEndpoint.h"

#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace rest {

	PatientsGetAllEndpoint::PatientsGetAllEndpoint(model::PatientMgr& patientMgr,
											 const dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 const systelab::json::IJSONAdapter& jsonAdapter)
		:EntityGetAllEndpoint(patientMgr,
							  std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
							  jsonAdapter)
	{
	}

}}

