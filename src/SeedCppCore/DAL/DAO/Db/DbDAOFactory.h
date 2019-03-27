#pragma once

#include "IDbDAOFactory.h"
#include "DAL/DAO/ITransactionDAOMgr.h"

namespace seed_cpp {
	class Core;
}

namespace seed_cpp { namespace dal {

	class DbDAOFactory : public IDbDAOFactory, public ITransactionDAOMgr
	{
	public:
		DbDAOFactory(Core&);
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

		void releaseTransactionInProgress();

	protected:
		Core& m_core;
		bool m_transactionInProgress;
	};

}}
