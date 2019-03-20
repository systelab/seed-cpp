#include "stdafx.h"
#include "TimeService.h"


namespace seed_cpp { namespace service {

	TimeService::TimeService()
	{
	}

	TimeService::~TimeService()
	{
	}

	boost::posix_time::ptime TimeService::getCurrentLocalTime() const
	{
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		return now;
	}

	boost::posix_time::ptime TimeService::getCurrentUTCTime() const
	{
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
		return now;
	}

}}
