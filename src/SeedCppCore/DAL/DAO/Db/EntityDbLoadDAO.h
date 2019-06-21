#pragma once

#include "DAL/DAO/ILoadDAO.h"
#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/ITableRecord.h"

namespace seed_cpp { namespace dal {

	template<typename _Entity, typename _EntityMgr>
	class EntityDbLoadDAO : public ILoadDAO
	{
	private:
		typedef std::function<std::unique_ptr<IDatabaseEntityTranslator>(_Entity&)> TranslatorFactoryMethod;
	public:
		EntityDbLoadDAO(const std::string& tableName,
						systelab::db::IDatabase& db,
						_EntityMgr& model,
						const TranslatorFactoryMethod& factoryMethod)
			:m_tableName(tableName)
			,m_db(db)
			,m_model(model)
			,m_factoryMethod(factoryMethod)
		{
		}

		virtual ~EntityDbLoadDAO() = default;

		void loadAll() const override
		{
			std::vector< std::unique_ptr<_Entity> > items;
			auto& itemsTable = m_db.getTable(m_tableName);
			auto itemsRecordset = itemsTable.getAllRecords();
			while (itemsRecordset->isCurrentRecordValid())
			{
				const auto& itemRecord = itemsRecordset->getCurrentRecord();

				auto newItem = std::make_unique<_Entity>();
				loadEntity(itemRecord, *newItem);
				items.push_back(std::move(newItem));

				itemsRecordset->nextRecord();
			}

			typename _EntityMgr::UniqueLock writeLock(m_model);
			m_model.setEntities(std::move(items), writeLock);
		};

	protected:
		void loadEntity(const systelab::db::ITableRecord& src, _Entity& trg) const
		{
			auto translator = m_factoryMethod(trg);
			translator->fillEntityFromRecord(src);
		}

	private:
		const std::string m_tableName;
		systelab::db::IDatabase& m_db;
		_EntityMgr& m_model;
		const TranslatorFactoryMethod m_factoryMethod;
	};

}}