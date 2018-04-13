#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>


namespace seed_cpp { namespace service {

	class ITimeService
	{
	public:
		virtual ~ITimeService() {};

		virtual boost::posix_time::ptime getCurrentLocalTime() const = 0;
		virtual boost::posix_time::ptime getCurrentUTCTime() const = 0;
	};

}}
