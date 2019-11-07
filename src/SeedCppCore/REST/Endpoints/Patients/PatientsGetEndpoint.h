#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetEndpoint.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace rest {

	class PatientsGetEndpoint : public EntityGetEndpoint<model::Patient, model::PatientMgr>
	{
	public:
		PatientsGetEndpoint(model::PatientMgr&,
							const dal::IJSONTranslatorsFactory&,
							const systelab::json::IJSONAdapter&);
	};

}}

