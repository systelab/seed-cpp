#pragma once

#include <memory>
#include <string>


namespace systelab { namespace json_adapter {

	class IJSONDocument;

	class IJSONAdapter
	{
	public:
		virtual ~IJSONAdapter() {};

		virtual std::unique_ptr<IJSONDocument> buildEmptyDocument() const = 0;
		virtual std::unique_ptr<IJSONDocument> buildDocumentFromString(const std::string&) const = 0;
	};

}}
