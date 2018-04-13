#pragma once

#include "Services/System/ITimeService.h"


namespace seed_cpp { namespace service {

	class TimeService : public ITimeService
	{
	public:
		TimeService();
		virtual ~TimeService();

		boost::posix_time::ptime getCurrentLocalTime() const;
		boost::posix_time::ptime getCurrentUTCTime() const;
	};

}}
