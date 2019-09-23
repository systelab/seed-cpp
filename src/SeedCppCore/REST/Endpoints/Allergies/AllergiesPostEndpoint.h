#pragma once

#include "SeedCppCore/REST/Endpoints/EntityPostEndpoint.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Services/Model/IAllergyModelService.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace service {
		class IJSONValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class AllergiesPostEndpoint : public EntityPostEndpoint<model::Allergy, service::IAllergyModelService>
	{
	public:
		AllergiesPostEndpoint(const dal::IJSONTranslatorsFactory&,
							  service::IAllergyModelService&,
							  const service::IJSONValidatorService&,
							  const systelab::json::IJSONAdapter&);
	};

}}
