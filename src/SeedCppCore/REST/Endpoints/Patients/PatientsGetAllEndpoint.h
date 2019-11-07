#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetAllEndpoint.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace seed_cpp { namespace rest {

	class PatientsGetAllEndpoint : public EntityGetAllEndpoint<model::Patient, model::PatientMgr>
	{
	public:
		PatientsGetAllEndpoint(model::PatientMgr&,
							   const dal::IJSONTranslatorsFactory&,
							   const systelab::json::IJSONAdapter&);
	};

}}

