#pragma once

#include <string>


namespace systelab { namespace json_adapter {

	class IJSONValue;

	class IJSONDocument
	{
	public:
		virtual ~IJSONDocument() {};

		virtual IJSONValue& getRootValue() = 0;
		virtual const IJSONValue& getRootValue() const = 0;

		virtual std::string serialize() const = 0;
	};

}}
