#pragma once

#include "SeedCppCore/DAL/DAO/ITransactionDAOMgr.h"
#include "SeedCppCore/DAL/DAO/Db/IDbDAOFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace dal {

	class DbDAOFactory : public IDbDAOFactory, public ITransactionDAOMgr
	{
	public:
		DbDAOFactory(Context&);
		virtual ~DbDAOFactory();

		std::unique_ptr<ILoadDAO> buildPatientLoadDAO();
		std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient &);

		// Users
		std::unique_ptr<ILoadDAO> buildUserLoadDAO();
		std::unique_ptr<ISaveDAO> buildUserSaveDAO(model::User &);

		// Transactions
		std::unique_ptr<ITransactionDAO> startTransaction();

		void releaseTransactionInProgress();

	protected:
		Context& m_context;
		bool m_transactionInProgress;
	};

}}
