#pragma once

#include <memory>
#include <string>


namespace systelab { namespace json_adapter {

	class IJSONDocument;

	class IJSONAdapter
	{
	public:
		virtual ~IJSONAdapter() {};

		virtual std::unique_ptr<IJSONDocument> buildDocument() = 0;
		virtual std::unique_ptr<IJSONDocument> parseDocument(const std::string&) = 0;
	};

}}
