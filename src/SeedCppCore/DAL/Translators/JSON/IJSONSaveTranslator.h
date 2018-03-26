#pragma once

#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"


namespace seed_cpp { namespace dal {

	class IJSONSaveTranslator
	{
	public:
		virtual ~IJSONSaveTranslator() {}

		virtual void saveEntityToJSON(systelab::json_adapter::IJSONValue&, systelab::json_adapter::IJSONDocument&) const = 0;
	};

}}

