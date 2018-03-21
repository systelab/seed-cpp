#include "stdafx.h"
#include "DbTransactionDAO.h"

#include "DAL/DAO/ITransactionDAOMgr.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/ITransaction.h"


namespace seed_cpp { namespace dal {

	DbTransactionDAO::DbTransactionDAO()
		:m_dbTransaction()
		,m_transactionMgr(0)
	{
	}

	DbTransactionDAO::DbTransactionDAO(systelab::db::IDatabase& database,
									   ITransactionDAOMgr& transactionMgr)
		:m_dbTransaction(database.startTransaction())
		,m_transactionMgr(&transactionMgr)
	{
	}

	DbTransactionDAO::~DbTransactionDAO()
	{
		m_dbTransaction.reset();
		if (m_transactionMgr)
		{
			m_transactionMgr->releaseTransactionInProgress();
		}
	}

	void DbTransactionDAO::commit()
	{
		if (m_dbTransaction)
		{
			m_dbTransaction->commit();
		}
	}

	void DbTransactionDAO::rollback()
	{
		if (m_dbTransaction)
		{
			m_dbTransaction->rollback();
		}
	}

}}