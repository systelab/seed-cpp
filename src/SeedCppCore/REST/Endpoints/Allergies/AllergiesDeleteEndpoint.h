#pragma once

#include "SeedCppCore/REST/Endpoints/EntityDeleteEndpoint.h"
#include "SeedCppCore/Services/Model/IAllergyModelService.h"


namespace seed_cpp { namespace rest {

	class AllergiesDeleteEndpoint : public EntityDeleteEndpoint<service::IAllergyModelService>
	{
	public:
		AllergiesDeleteEndpoint(service::IAllergyModelService&);
	};

}}
