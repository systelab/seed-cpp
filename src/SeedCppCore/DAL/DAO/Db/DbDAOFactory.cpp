#include "stdafx.h"
#include "DbDAOFactory.h"

#include "Core.h"
#include "DAL/DAO/Db/AllergyDbLoadDAO.h"
#include "DAL/DAO/Db/DbTransactionDAO.h"
#include "DAL/DAO/Db/PatientDbLoadDAO.h"
#include "DAL/DAO/Db/PatientDbSaveDAO.h"
#include "DAL/DAO/Db/UserDbLoadDAO.h"
#include "DAL/DAO/Db/UserDbSaveDAO.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/Model.h"


namespace seed_cpp { namespace dal {

	DbDAOFactory::DbDAOFactory(Core& core)
		:m_core(core)
		,m_transactionInProgress(false)
	{
	}

	DbDAOFactory::~DbDAOFactory() = default;

	// Load
	std::unique_ptr<ILoadDAO> DbDAOFactory::buildAllergyLoadDAO()
	{
		auto& database = m_core.getDatabase();
		auto& model = m_core.getModel().getAllergyMgr();
		auto& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();

		return std::make_unique<AllergyDbLoadDAO>("Allergy", database, model, dbTranslatorsFactory,
													std::bind(&IDbTranslatorsFactory::buildAllergyTranslator, &dbTranslatorsFactory, std::placeholders::_1));
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildPatientLoadDAO()
	{
		auto& database = m_core.getDatabase();
		auto& model = m_core.getModel().getPatientMgr();
		auto& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();

		return std::make_unique<PatientDbLoadDAO>(database, model, dbTranslatorsFactory);
	}

	std::unique_ptr<ILoadDAO> DbDAOFactory::buildUserLoadDAO()
	{
		auto& database = m_core.getDatabase();
		auto& model = m_core.getModel().getUserMgr();
		auto& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();

		return std::make_unique<UserDbLoadDAO>(database, model, dbTranslatorsFactory);
	}

	// Save
	std::unique_ptr<ISaveDAO> DbDAOFactory::buildPatientSaveDAO(model::Patient& patient)
	{
		auto& database = m_core.getDatabase();
		auto& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();

		return std::make_unique<PatientDbSaveDAO>(database, patient, *this, dbTranslatorsFactory);
	}

	std::unique_ptr<ISaveDAO> DbDAOFactory::buildUserSaveDAO(model::User& user)
	{
		auto& database = m_core.getDatabase();
		auto& dbTranslatorsFactory = m_core.getDbTranslatorsFactory();

		return std::make_unique<UserDbSaveDAO>(database, user, *this, dbTranslatorsFactory);
	}

	// Transaction
	std::unique_ptr<ITransactionDAO> DbDAOFactory::startTransaction()
	{
		if (!m_transactionInProgress)
		{
			auto& database = m_core.getDatabase();
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
