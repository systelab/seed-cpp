#pragma once

#include "SeedCppCoreTestUtilities/Mocks/Services/System/MockTimeService.h"


namespace seed_cpp { namespace test_utility {

	class StubTimeService : public MockTimeService
	{
	public:
		StubTimeService();
		virtual ~StubTimeService();

		void setCurrentTime(const boost::posix_time::ptime& newCurrentTime);

		void addMilliseconds(unsigned int nMilliseconds);
		void addSeconds(unsigned int nSeconds);
		void addMinutes(unsigned int nMinutes);
		void addHours(unsigned int nHours);

	private:
		boost::posix_time::ptime m_currentTime;
	};

}}

