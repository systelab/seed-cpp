#include "stdafx.h"
#include "StubTimeService.h"

#include <chrono>


using namespace testing;

namespace seed_cpp { namespace test_utility {

	StubTimeService::StubTimeService()
		:m_currentTime(boost::posix_time::microsec_clock::universal_time())
	{
		ON_CALL(*this, getCurrentLocalTime()).WillByDefault(Invoke(
			[this]() -> boost::posix_time::ptime
			{
				return m_currentTime;
			}
		));

		ON_CALL(*this, getCurrentUTCTime()).WillByDefault(Invoke(
			[this]() -> boost::posix_time::ptime
			{
				return m_currentTime;
			}
		));
	}

	StubTimeService::~StubTimeService() = default;

	void StubTimeService::setCurrentTime(const boost::posix_time::ptime& newCurrentTime)
	{
		m_currentTime = newCurrentTime;
	}

	void StubTimeService::addMilliseconds(unsigned int nMilliseconds)
	{
		m_currentTime += boost::posix_time::milliseconds(nMilliseconds);
	}

	void StubTimeService::addSeconds(unsigned int nSeconds)
	{
		m_currentTime += boost::posix_time::seconds(nSeconds);
	}

	void StubTimeService::addMinutes(unsigned int nMinutes)
	{
		m_currentTime += boost::posix_time::minutes(nMinutes);
	}

	void StubTimeService::addHours(unsigned int nHours)
	{
		m_currentTime += boost::posix_time::hours(nHours);
	}

}}

