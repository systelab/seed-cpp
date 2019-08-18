#include "stdafx.h"
#include "PatientsDeleteEndpoint.h"


namespace seed_cpp { namespace rest {

	PatientsDeleteEndpoint::PatientsDeleteEndpoint(service::IPatientModelService& patientModelService)
		:EntityDeleteEndpoint(patientModelService)
	{
	}

}}

