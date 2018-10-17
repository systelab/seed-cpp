#pragma once

#include <string>


namespace systelab { namespace json_adapter {

	class IJSONSchemaValidator;

	class IJSONRemoteSchemaProvider
	{
	public:
		virtual ~IJSONRemoteSchemaProvider() {};

		virtual std::unique_ptr<IJSONDocument> getRemoteSchemaDocument(const std::string& uri) const = 0;
	};

}}
