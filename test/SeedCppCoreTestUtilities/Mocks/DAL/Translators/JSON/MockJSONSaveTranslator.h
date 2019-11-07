#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONSaveTranslator.h"


namespace seed_cpp { namespace test_utility {

	class MockJSONSaveTranslator : public dal::IJSONSaveTranslator
	{
	public:
		MockJSONSaveTranslator();
		virtual ~MockJSONSaveTranslator();

		MOCK_CONST_METHOD1(saveEntityToJSON, void(systelab::json::IJSONValue&));
	};

}}
