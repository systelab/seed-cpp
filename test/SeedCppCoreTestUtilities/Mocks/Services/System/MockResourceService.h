#pragma once

#include "SeedCppCore/Services/System/IResourceService.h"


namespace seed_cpp { namespace test_utility {

	class MockResourceService : public service::IResourceService
	{
	public:
		MockResourceService();
		virtual ~MockResourceService();

		MOCK_CONST_METHOD2(loadResourceAsString, std::string(unsigned int, const std::string&));
		MOCK_CONST_METHOD2(loadResourceAsString, std::string(const std::string&, const std::string&));
	};

}}
