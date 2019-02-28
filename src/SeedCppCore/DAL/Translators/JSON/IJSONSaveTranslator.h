#pragma once

#include "IJSONDocument.h"
#include "IJSONValue.h"


namespace seed_cpp { namespace dal {

	class IJSONSaveTranslator
	{
	public:
		virtual ~IJSONSaveTranslator() {}

		virtual void saveEntityToJSON(systelab::json_adapter::IJSONValue&) const = 0;
	};

}}

