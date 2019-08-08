#pragma once

#include "SeedCppCore/Services/Model/IModelInitializationService.h"


namespace seed_cpp { namespace test_utility {

	class MockModelInitializationService : public service::IModelInitializationService
	{
	public:
		MockModelInitializationService();
		virtual ~MockModelInitializationService();

		MOCK_CONST_METHOD0(initialize, void());
	};

}}
