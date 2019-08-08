#pragma once

#include "SeedCppCore/Services/System/ITimeService.h"


namespace seed_cpp { namespace test_utility {

	class MockTimeService : public service::ITimeService
	{
	public:
		MockTimeService();
		virtual ~MockTimeService();

		MOCK_CONST_METHOD0(getCurrentLocalTime, boost::posix_time::ptime());
		MOCK_CONST_METHOD0(getCurrentUTCTime, boost::posix_time::ptime());
	};

}}
