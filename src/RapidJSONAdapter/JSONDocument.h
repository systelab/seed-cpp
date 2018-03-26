#pragma once

#include "JSONAdapterInterface/IJSONDocument.h"

#include <memory>
#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONDocument : public IJSONDocument
	{
	public:
		JSONDocument(std::unique_ptr<rapidjson::Document>);
		virtual ~JSONDocument();

		IJSONValue& getRootValue();
		const IJSONValue& getRootValue() const;

	private:
		std::unique_ptr<rapidjson::Document> m_document;
		std::unique_ptr<IJSONValue> m_rootValue;
	};

}}}
