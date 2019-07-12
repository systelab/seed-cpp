#pragma once

#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/ITransactionDAO.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"

#include "DbAdapterInterface/IDatabase.h"

namespace seed_cpp { namespace dal {

	template<typename _Entity>
	class EntityDbSaveDAO : public ISaveDAO
	{
	private:
		typedef std::function<std::unique_ptr<IDatabaseEntityTranslator>(_Entity&)> TranslatorFactoryMethod;

	public:
		EntityDbSaveDAO(const std::string& tableName,
						systelab::db::IDatabase& db,
						_Entity& entity,
						IDbDAOFactory& daoFactory,
						const TranslatorFactoryMethod& factoryMethod)
			:m_tableName(tableName)
			,m_db(db)
			,m_entity(entity)
			,m_daoFactory(daoFactory)
			,m_factoryMethod(factoryMethod)
		{
		}

		virtual ~EntityDbSaveDAO() = default;

		void addEntity() override
		{
			if (!m_entity.getId())
			{
				throw std::runtime_error("Attempting to add an entity without id in table " + m_tableName);
			}

			std::unique_ptr<dal::ITransactionDAO> transaction;
			try
			{
				transaction = m_daoFactory.startTransaction();

				auto& itemsTable = m_db.getTable(m_tableName);
				auto itemRecord = itemsTable.createRecord();
				auto itemTranslator = m_factoryMethod(m_entity);
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

		void updateEntity() override
		{
			if (!m_entity.getId())
			{
				throw std::runtime_error("Attempting to update an entity without id in table "+ m_tableName);
			}

			std::unique_ptr<dal::ITransactionDAO> transaction;
			try
			{
				transaction = m_daoFactory.startTransaction();

				auto& itemsTable = m_db.getTable(m_tableName);
				auto itemRecord = itemsTable.createRecord();
				auto itemTranslator = m_factoryMethod(m_entity);
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

		void deleteEntity() override
		{
			if (!m_entity.getId())
			{
				throw std::runtime_error("Attempting to delete an entity without id in table "+ m_tableName);
			}

			std::unique_ptr<dal::ITransactionDAO> transaction;
			try
			{
				transaction = m_daoFactory.startTransaction();

				auto& table = m_db.getTable(m_tableName);
				auto record = table.createRecord();
				auto itemTranslator = m_factoryMethod(m_entity);
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

	private:
		const std::string m_tableName;
		systelab::db::IDatabase& m_db;
		_Entity& m_entity;
		IDbDAOFactory& m_daoFactory;
		const TranslatorFactoryMethod m_factoryMethod;
	};

}}