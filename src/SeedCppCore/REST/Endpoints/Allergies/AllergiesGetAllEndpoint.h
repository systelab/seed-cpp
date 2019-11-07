#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetAllEndpoint.h"
#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace seed_cpp { namespace rest {

	class AllergiesGetAllEndpoint : public EntityGetAllEndpoint<model::Allergy, model::AllergyMgr>
	{
	public:
		AllergiesGetAllEndpoint(model::AllergyMgr&,
								const dal::IJSONTranslatorsFactory&,
								const systelab::json::IJSONAdapter&);
	};

}}
