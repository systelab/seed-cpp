#pragma once

#include "JSONAdapterInterface/IJSONDocument.h"

#include <memory>
#include <vector>

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONDocument : public IJSONDocument
	{
	public:
		JSONDocument(std::unique_ptr<rapidjson::Document>);
		virtual ~JSONDocument();

		IJSONValue& getRootValue();
		const IJSONValue& getRootValue() const;

		std::string serialize() const;

	public:
		void addFreeValue(std::unique_ptr<rapidjson::Value>);
		std::unique_ptr<rapidjson::Value> removeFreeValue(const rapidjson::Value&);

	private:
		std::unique_ptr<rapidjson::Document> m_document;
		std::unique_ptr<IJSONValue> m_rootValue;
		std::vector< std::unique_ptr<rapidjson::Value> > m_freeValues;
	};

}}}
