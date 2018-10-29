#include "StdAfx.h"
#include "UserDbSaveDAO.h"

#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/ITransactionDAO.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/User.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/ITable.h"


namespace seed_cpp { namespace dal {

	UserDbSaveDAO::UserDbSaveDAO(systelab::db::IDatabase& db,
								 model::User& item,
								 dal::IDbDAOFactory& daoFactory,
								 dal::IDbTranslatorsFactory& translatorsFactory)
		:m_db(db)
		,m_item(item)
		,m_daoFactory(daoFactory)
		,m_translatorsFactory(translatorsFactory)
	{
	}

	void UserDbSaveDAO::addEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::exception( "Attempting to add a user without an ID to database." );
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			systelab::db::ITable& itemsTable = m_db.getTable("User");
			std::unique_ptr<systelab::db::ITableRecord> itemRecord = itemsTable.createRecord();

			std::unique_ptr<dal::IDatabaseEntityTranslator> itemTranslator = m_translatorsFactory.buildUserTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*itemRecord);
			itemsTable.insertRecord(*itemRecord);

			transaction->commit();
		}
		catch (std::exception& exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

	void UserDbSaveDAO::updateEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::exception( "Attempting to update a user without id in database." );
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			systelab::db::ITable& itemsTable = m_db.getTable("User");
			std::unique_ptr<systelab::db::ITableRecord> itemRecord = itemsTable.createRecord();

			std::unique_ptr<dal::IDatabaseEntityTranslator> itemTranslator = m_translatorsFactory.buildUserTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*itemRecord);
			itemsTable.updateRecord(*itemRecord);

			transaction->commit();
		}
		catch (std::exception& exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

	void UserDbSaveDAO::deleteEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::exception( "Attempting to delete a user without id in database." );
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			systelab::db::ITable& table = m_db.getTable("User");
			auto record = table.createRecord();
			std::unique_ptr<dal::IDatabaseEntityTranslator> itemTranslator = m_translatorsFactory.buildUserTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*record);
			table.deleteRecord(*record);

			transaction->commit();
		}
		catch (std::exception& exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

}}
