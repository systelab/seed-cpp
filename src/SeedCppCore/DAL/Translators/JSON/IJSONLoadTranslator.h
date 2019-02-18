#pragma once

#include "IJSONValue.h"


namespace seed_cpp { namespace dal {

	class IJSONLoadTranslator
	{
	public:
		virtual ~IJSONLoadTranslator() {}

		virtual void loadEntityFromJSON(const systelab::json_adapter::IJSONValue&) = 0;
	};

}}

