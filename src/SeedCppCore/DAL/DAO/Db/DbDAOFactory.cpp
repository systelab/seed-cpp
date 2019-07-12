#include "stdafx.h"
#include "DbDAOFactory.h"

#include "Context.h"
#include "DAL/DbConstants.h"
#include "DAL/DAO/Db/AllergyDbLoadDAO.h"
#include "DAL/DAO/Db/AllergyDbSaveDAO.h"
#include "DAL/DAO/Db/DbTransactionDAO.h"
#include "DAL/DAO/Db/PatientDbLoadDAO.h"
#include "DAL/DAO/Db/PatientDbSaveDAO.h"
#include "DAL/DAO/Db/UserDbLoadDAO.h"
#include "DAL/DAO/Db/UserDbSaveDAO.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/Model.h"


namespace seed_cpp { namespace dal {

	DbDAOFactory::DbDAOFactory(Context& context)
		:m_context(context)
		,m_transactionInProgress(false)
	{
	}

	DbDAOFactory::~DbDAOFactory() = default;

	// Load
	std::unique_ptr<ILoadDAO> DbDAOFactory::buildAllergyLoadDAO()
	{
		auto& database = m_context.getDatabase();
		auto& model = m_context.getModel()->getAllergyMgr();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<AllergyDbLoadDAO>(db_table::ALLERGY, database, model,
													std::bind(&IDbTranslatorsFactory::buildAllergyTranslator, &dbTranslatorsFactory, std::placeholders::_1));
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildPatientLoadDAO()
	{
		auto& database = m_context.getDatabase();
		auto& model = m_context.getModel()->getPatientMgr();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<PatientDbLoadDAO>(database, model, dbTranslatorsFactory);
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildUserLoadDAO()
	{
		auto& database = m_context.getDatabase();
		auto& model = m_context.getModel()->getUserMgr();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<UserDbLoadDAO>(db_table::USER, database, model,
												std::bind(&IDbTranslatorsFactory::buildUserTranslator, &dbTranslatorsFactory, std::placeholders::_1));
	}

	// Save
	std::unique_ptr<ISaveDAO> DbDAOFactory::buildAllergySaveDAO(model::Allergy& entity)
	{
		auto& database = m_context.getDatabase();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<AllergyDbSaveDAO>(db_table::ALLERGY, database, entity, *this,
												  std::bind(&IDbTranslatorsFactory::buildAllergyTranslator, &dbTranslatorsFactory, std::placeholders::_1));
	}
	std::unique_ptr<ISaveDAO> DbDAOFactory::buildPatientSaveDAO(model::Patient& patient)
	{
		auto& database = m_context.getDatabase();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<PatientDbSaveDAO>(database, patient, *this, dbTranslatorsFactory);
	}

	std::unique_ptr<ISaveDAO> DbDAOFactory::buildUserSaveDAO(model::User& entity)
	{
		auto& database = m_context.getDatabase();
		auto& dbTranslatorsFactory = *m_context.getDbTranslatorsFactory();

		return std::make_unique<UserDbSaveDAO>(db_table::USER, database, entity, *this,
											   std::bind(&IDbTranslatorsFactory::buildUserTranslator, &dbTranslatorsFactory, std::placeholders::_1));
	}

	// Transaction
	std::unique_ptr<ITransactionDAO> DbDAOFactory::startTransaction()
	{
		if (!m_transactionInProgress)
		{
			auto& database = m_context.getDatabase();
			m_transactionInProgress = true;
			return std::make_unique<DbTransactionDAO>(database, *this);
		}
		else
		{
			return std::make_unique<DbTransactionDAO>();
		}
	}

	void DbDAOFactory::releaseTransactionInProgress()
	{
		m_transactionInProgress = false;
	}

}}
