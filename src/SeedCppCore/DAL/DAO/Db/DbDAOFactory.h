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

		// Load
		std::unique_ptr<ILoadDAO> buildAllergyLoadDAO() override;
		std::unique_ptr<ILoadDAO> buildPatientLoadDAO() override;
		std::unique_ptr<ILoadDAO> buildUserLoadDAO() override;

		// Save
		std::unique_ptr<ISaveDAO> buildAllergySaveDAO(model::Allergy&) override;
		std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient&) override;
		std::unique_ptr<ISaveDAO> buildUserSaveDAO(model::User&) override;

		// Transactions
		std::unique_ptr<ITransactionDAO> startTransaction() override;

		void releaseTransactionInProgress() override;

	protected:
		Context& m_context;
		bool m_transactionInProgress;
	};

}}
