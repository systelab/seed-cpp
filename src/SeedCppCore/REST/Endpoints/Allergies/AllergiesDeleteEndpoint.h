#pragma once

#include "REST/Endpoints/EntityDeleteEndpoint.h"
#include "Services/Model/IAllergyModelService.h"


namespace seed_cpp { namespace rest {

	class AllergiesDeleteEndpoint : public EntityDeleteEndpoint<service::IAllergyModelService>
	{
	public:
		AllergiesDeleteEndpoint(service::IAllergyModelService&);
	};

}}
