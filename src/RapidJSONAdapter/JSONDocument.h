#pragma once

#include "JSONAdapterInterface/IJSONDocument.h"

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONDocument : public IJSONDocument
	{
	public:
		JSONDocument(rapidjson::Document&);
		virtual ~JSONDocument();

		IJSONValue& getRootValue();
		const IJSONValue& getRootValue() const;

		std::unique_ptr<IJSONValue> buildValue();

	private:
		rapidjson::Document& m_document;
		std::unique_ptr<IJSONValue> m_rootValue;
	};

}}}
