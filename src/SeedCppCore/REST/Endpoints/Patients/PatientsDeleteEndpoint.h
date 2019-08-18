#pragma once

#include "REST/Endpoints/EntityDeleteEndpoint.h"
#include "Services/Model/IPatientModelService.h"


namespace seed_cpp { namespace rest {

	class PatientsDeleteEndpoint : public EntityDeleteEndpoint<service::IPatientModelService>
	{
	public:
		PatientsDeleteEndpoint(service::IPatientModelService&);
	};

}}

