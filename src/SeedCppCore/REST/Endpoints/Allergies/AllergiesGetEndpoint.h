#pragma once

#include "SeedCppCore/REST/Endpoints/EntityGetEndpoint.h"
#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"


namespace seed_cpp { namespace dal {
	class IJSONTranslatorsFactory;
}}

namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace rest {

	class AllergiesGetEndpoint : public EntityGetEndpoint<model::Allergy, model::AllergyMgr>
	{
	public:
		AllergiesGetEndpoint(model::AllergyMgr&,
							 const dal::IJSONTranslatorsFactory&,
							 const systelab::json::IJSONAdapter&);
	};

}}