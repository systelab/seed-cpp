#pragma once

#include "SeedCppCore/REST/Endpoints/EntityPostEndpoint.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Services/Model/IPatientModelService.h"


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

	class PatientsPostEndpoint : public EntityPostEndpoint<model::Patient, service::IPatientModelService>
	{
	public:
		PatientsPostEndpoint(const dal::IJSONTranslatorsFactory&,
							 service::IPatientModelService&,
							 const service::IJSONValidatorService&,
							 const systelab::json::IJSONAdapter&);
	};

}}
