#include "StdAfx.h"
#include "UserDbLoadDAO.h"

#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/User.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/IFieldValue.h"
#include "DbAdapterInterface/ITable.h"
#include "DbAdapterInterface/ITableRecord.h"


namespace seed_cpp { namespace dal {

	UserDbLoadDAO::UserDbLoadDAO(systelab::db::IDatabase& db,
								 model::EntityMgr<model::User>& model,
								 dal::IDbTranslatorsFactory& translatorsFactory)
		:m_db(db)
		,m_model(model)
		,m_translatorsFactory(translatorsFactory)
	{
	}

	void UserDbLoadDAO::loadAll() const
	{
		std::vector< std::unique_ptr<model::User> > items;
		systelab::db::ITable& itemsTable = m_db.getTable("User");
		std::unique_ptr<systelab::db::ITableRecordSet> itemsRecordset = itemsTable.getAllRecords();
		while (itemsRecordset->isCurrentRecordValid())
		{
			const systelab::db::ITableRecord& itemRecord = itemsRecordset->getCurrentRecord();

			std::unique_ptr<model::User> newItem(new model::User());
			loadUser(itemRecord, *newItem);
			items.push_back(std::move(newItem) );

			itemsRecordset->nextRecord();
		}

		m_model.setEntities(std::move(items));
	}

	void UserDbLoadDAO::loadUser(const systelab::db::ITableRecord& src, model::User& patient) const
	{
		namespace sdb = systelab::db;
		std::unique_ptr<IDatabaseEntityTranslator> translator = m_translatorsFactory.buildUserTranslator(patient);
		translator->fillEntityFromRecord(src);
	}

}}