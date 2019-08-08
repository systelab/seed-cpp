#pragma once

#include "SeedCppCore/Services/Model/IModelLoaderService.h"


namespace seed_cpp { namespace test_utility {

	class MockModelLoaderService : public service::IModelLoaderService
	{
	public:
		MockModelLoaderService();
		virtual ~MockModelLoaderService();

		MOCK_CONST_METHOD0(loadModel, void());
	};

}}
