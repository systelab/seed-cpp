#include "stdafx.h"
#include "AllergiesDeleteEndpoint.h"


namespace seed_cpp { namespace rest {

	AllergiesDeleteEndpoint::AllergiesDeleteEndpoint(service::IAllergyModelService& allergyModelService)
		:EntityDeleteEndpoint(allergyModelService)
	{
	}

}}

