#pragma once

#include "SeedCppCore/Services/System/IContextBuilderService.h"


namespace seed_cpp { namespace test_utility {

	class MockContextBuilderService : public service::IContextBuilderService
	{
	public:
		MockContextBuilderService();
		virtual ~MockContextBuilderService();

		MOCK_METHOD0(buildFactories, void());
		MOCK_METHOD0(buildModel, void());
		MOCK_METHOD0(buildServices, void());
	};

}}
