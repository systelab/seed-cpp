#pragma once

#include "JSONAdapterInterface/IJSONAdapter.h"

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONAdapter : public IJSONAdapter
	{
	public:
		JSONAdapter();
		virtual ~JSONAdapter();

		std::unique_ptr<IJSONDocument> buildEmptyDocument();
		std::unique_ptr<IJSONDocument> buildDocumentFromString(const std::string&);
	};

}}}