#pragma once

#include "IJSONAdapter.h"

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONAdapter : public IJSONAdapter
	{
	public:
		JSONAdapter();
		virtual ~JSONAdapter();

		std::unique_ptr<IJSONDocument> buildEmptyDocument() const;
		std::unique_ptr<IJSONDocument> buildDocumentFromString(const std::string&) const;

		std::unique_ptr<IJSONSchemaValidator> buildSchemaValidator(const IJSONDocument&) const;
		std::unique_ptr<IJSONSchemaValidator> buildSchemaValidator(const IJSONDocument&, const IJSONRemoteSchemaProvider&) const;
	};

}}}
