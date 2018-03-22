#include "StdAfx.h"
#include "DbDAOFactory.h"

#include "Core.h"
#include "DAL/DAO/Db/PatientDbLoadDAO.h"
#include "DAL/DAO/Db/PatientDbSaveDAO.h"
#include "DAL/DAO/Db/DbTransactionDAO.h"
#include "Model/Model.h"


namespace seed_cpp { namespace dal {

	DbDAOFactory::DbDAOFactory(Core& core)
		:m_core(core)
		,m_transactionInProgress(false)
	{
	}

	DbDAOFactory::~DbDAOFactory()
	{
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildPatientLoadDAO()
	{
		systelab::db::IDatabase& database = m_core.getDatabase();
		model::EntityMgr<model::Patient>& model = m_core.getModel().getPatientMgr();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();
		return std::unique_ptr<ILoadDAO>(new PatientDbLoadDAO(database, model, dbTranslatorsFactory));
	}

	std::unique_ptr<ISaveDAO> DbDAOFactory::buildPatientSaveDAO(model::Patient& patient)
	{
		systelab::db::IDatabase& database = m_core.getDatabase();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();
		return std::unique_ptr<ISaveDAO>(new PatientDbSaveDAO(database, patient, *this, dbTranslatorsFactory));
	}

	std::unique_ptr<ITransactionDAO> DbDAOFactory::startTransaction()
	{
		if (!m_transactionInProgress)
		{
			systelab::db::IDatabase& database = m_core.getDatabase();
			m_transactionInProgress = true;
			return std::unique_ptr<ITransactionDAO>(new DbTransactionDAO(database, *this));
		}
		else
		{
			return std::unique_ptr<ITransactionDAO>(new DbTransactionDAO());
		}
	}

	void DbDAOFactory::releaseTransactionInProgress()
	{
		m_transactionInProgress = false;
	}

}}