#pragma once

#include "SeedCppCore/Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONDocument.h"


namespace seed_cpp { namespace test_utility {

	class MockJSONValidatorService : public service::IJSONValidatorService
	{
	public:
		MockJSONValidatorService();
		virtual ~MockJSONValidatorService();

		MOCK_CONST_METHOD2(validate, void(const systelab::json::IJSONDocument&, const std::string&));
	};

}}
