#pragma once

#include <memory>
#include <string>


namespace systelab { namespace json_adapter {

	class IJSONDocument;

	class IJSONRemoteSchemaProvider
	{
	public:
		virtual ~IJSONRemoteSchemaProvider() {};

		virtual std::unique_ptr<IJSONDocument> getRemoteSchemaDocument(const std::string& uri) const = 0;
	};

}}
