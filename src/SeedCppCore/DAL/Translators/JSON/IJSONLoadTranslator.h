#pragma once

#include "JSONAdapterInterface/IJSONValue.h"


namespace seed_cpp { namespace dal {

	class IJSONLoadTranslator
	{
	public:
		virtual ~IJSONLoadTranslator() {}

		virtual void loadEntityFromJSON(const systelab::json::IJSONValue&) = 0;
	};

}}

