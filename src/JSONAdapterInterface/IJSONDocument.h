#pragma once

#include <memory>

namespace systelab { namespace json_adapter {

	class IJSONValue;

	class IJSONDocument
	{
	public:
		virtual ~IJSONDocument() {};

		virtual IJSONValue& getRootValue() = 0;
		virtual const IJSONValue& getRootValue() const = 0;

		virtual std::unique_ptr<IJSONValue> buildValue() = 0;
	};

}}
