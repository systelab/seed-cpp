#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONLoadTranslator.h"


namespace seed_cpp { namespace test_utility {

	class MockJSONLoadTranslator : public dal::IJSONLoadTranslator
	{
	public:
		MockJSONLoadTranslator();
		virtual ~MockJSONLoadTranslator();

		MOCK_METHOD1(loadEntityFromJSON, void(const systelab::json::IJSONValue&));
	};

}}
