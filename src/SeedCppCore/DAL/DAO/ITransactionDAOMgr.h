#pragma once

namespace seed_cpp { namespace dal {

	class ITransactionDAOMgr
	{
	public:
		virtual ~ITransactionDAOMgr() {}

		virtual void releaseTransactionInProgress() = 0;
	};

}}
