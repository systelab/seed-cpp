#pragma once

namespace seed_cpp { namespace dal {

	class ITransactionDAO
	{
	public:
		virtual ~ITransactionDAO() {}

		virtual void commit() = 0;
		virtual void rollback() = 0;
	};

}}
