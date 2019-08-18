#pragma once

#include "REST/Endpoints/EntityPutEndpoint.h"
#include "Model/Allergy.h"
#include "Services/Model/IAllergyModelService.h"


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

	class AllergiesPutEndpoint : public EntityPutEndpoint<model::Allergy, service::IAllergyModelService>
	{
	public:
		AllergiesPutEndpoint(const dal::IJSONTranslatorsFactory&,
							 service::IAllergyModelService&,
							 const service::IJSONValidatorService&,
							 const systelab::json::IJSONAdapter&);
	};

}}
