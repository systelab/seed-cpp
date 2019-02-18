#include "JSONDocument.h"

#include "JSONValue.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONDocument::JSONDocument(std::unique_ptr<rapidjson::Document> document)
		:m_document(std::move(document))
		,m_rootValue(std::make_unique<JSONValue>(*this, *m_document, m_document->GetAllocator()))
		,m_freeValues()
	{
	}

	JSONDocument::~JSONDocument()
	{
	}

	IJSONValue& JSONDocument::getRootValue()
	{
		return *m_rootValue;
	}

	const IJSONValue& JSONDocument::getRootValue() const
	{
		return *m_rootValue;
	}

	std::string JSONDocument::serialize() const
	{
		rapidjson::StringBuffer jsonBuffer;
		jsonBuffer.Clear();
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.SetMaxDecimalPlaces(6);
		m_document->Accept(jsonWriter);
		std::string serializedDocument = jsonBuffer.GetString();

		return serializedDocument;
	}

	void JSONDocument::addFreeValue(std::unique_ptr<rapidjson::Value> value)
	{
		m_freeValues.push_back(std::move(value));
	}

	std::unique_ptr<rapidjson::Value> JSONDocument::removeFreeValue(const rapidjson::Value& value)
	{
		for (auto it = m_freeValues.begin(); it != m_freeValues.end(); it++)
		{
			if (it->get() == &value)
			{
				std::unique_ptr<rapidjson::Value> foundValue;
				foundValue.swap(*it);
				m_freeValues.erase(it);
				return std::move(foundValue);
			}
		}

		return std::unique_ptr<rapidjson::Value>();
	}

}}}
