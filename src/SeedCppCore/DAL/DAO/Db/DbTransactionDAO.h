#pragma once

#include "DAL/DAO/ITransactionDAO.h"

#include <memory>


namespace systelab { namespace db {
	class IDatabase;
	class ITransaction;
}}

namespace seed_cpp { namespace dal {

	class ITransactionDAOMgr;

	class DbTransactionDAO : public ITransactionDAO
	{
	public:
		DbTransactionDAO();
		DbTransactionDAO(systelab::db::IDatabase&, ITransactionDAOMgr&);

		virtual ~DbTransactionDAO();

		void commit();
		void rollback();

	private:
		std::unique_ptr<systelab::db::ITransaction> m_dbTransaction;
		ITransactionDAOMgr* m_transactionMgr;
	};

}}
