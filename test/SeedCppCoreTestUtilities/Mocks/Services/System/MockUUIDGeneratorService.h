#pragma once

#include "SeedCppCore/Services/System/IUUIDGeneratorService.h"


namespace seed_cpp { namespace test_utility {

	class MockUUIDGeneratorService : public service::IUUIDGeneratorService
	{
	public:
		MockUUIDGeneratorService();
		virtual ~MockUUIDGeneratorService();

		MOCK_CONST_METHOD0(generateUUID, std::string());
	};

}}
