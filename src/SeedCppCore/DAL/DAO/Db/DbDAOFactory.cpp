#include "stdafx.h"
#include "DbDAOFactory.h"

#include "Context.h"
#include "DAL/DAO/Db/DbTransactionDAO.h"
#include "DAL/DAO/Db/PatientDbLoadDAO.h"
#include "DAL/DAO/Db/PatientDbSaveDAO.h"
#include "DAL/DAO/Db/UserDbLoadDAO.h"
#include "DAL/DAO/Db/UserDbSaveDAO.h"
#include "Model/Model.h"


namespace seed_cpp { namespace dal {

	DbDAOFactory::DbDAOFactory(Context& context)
		:m_context(context)
		,m_transactionInProgress(false)
	{
	}

	DbDAOFactory::~DbDAOFactory() = default;

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildPatientLoadDAO()
	{
		systelab::db::IDatabase& database = m_context.getDatabase();
		model::EntityMgr<model::Patient>& model = m_context.getModel()->getPatientMgr();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();
		return std::unique_ptr<ILoadDAO>(new PatientDbLoadDAO(database, model, dbTranslatorsFactory));
	}

	std::unique_ptr<ISaveDAO> DbDAOFactory::buildPatientSaveDAO(model::Patient& patient)
	{
		systelab::db::IDatabase& database = m_context.getDatabase();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();
		return std::unique_ptr<ISaveDAO>(new PatientDbSaveDAO(database, patient, *this, dbTranslatorsFactory));
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildUserLoadDAO()
	{
		systelab::db::IDatabase& database = m_context.getDatabase();
		model::EntityMgr<model::User>& model = m_context.getModel()->getUserMgr();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();
		return std::unique_ptr<ILoadDAO>(new UserDbLoadDAO(database, model, dbTranslatorsFactory));
	}

	std::unique_ptr<ISaveDAO> DbDAOFactory::buildUserSaveDAO(model::User& user)
	{
		systelab::db::IDatabase& database = m_context.getDatabase();
		dal::IDbTranslatorsFactory& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();
		return std::unique_ptr<ISaveDAO>(new UserDbSaveDAO(database, user, *this, dbTranslatorsFactory));
	}

	std::unique_ptr<ITransactionDAO> DbDAOFactory::startTransaction()
	{
		if (!m_transactionInProgress)
		{
			systelab::db::IDatabase& database = m_context.getDatabase();
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
