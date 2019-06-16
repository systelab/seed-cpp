#pragma once

#include "SeedCppCore/Services/System/IUUIDGeneratorService.h"


namespace seed_cpp { namespace test_utility {

	class MockUUIDGeneratorService : public service::IUUIDGeneratorService
	{
	public:
		MockUUIDGeneratorService();
		virtual ~MockUUIDGeneratorService();

		MOCK_CONST_METHOD2(loadResourceAsString, std::string(unsigned int, const std::string&));
		MOCK_CONST_METHOD2(loadResourceAsString, std::string(const std::string&, const std::string&));
	};

}}
