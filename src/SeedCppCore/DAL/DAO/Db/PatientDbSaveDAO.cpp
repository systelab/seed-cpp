#include "stdafx.h"
#include "PatientDbSaveDAO.h"

#include "DAL/DbConstants.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/ITransactionDAO.h"
#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/Address.h"
#include "Model/Patient.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/ITable.h"


namespace seed_cpp { namespace dal {

	PatientDbSaveDAO::PatientDbSaveDAO(systelab::db::IDatabase& db,
									   model::Patient& item,
									   dal::IDbDAOFactory& daoFactory,
									   dal::IDbTranslatorsFactory& translatorsFactory)
		:m_db(db)
		,m_item(item)
		,m_daoFactory(daoFactory)
		,m_translatorsFactory(translatorsFactory)
	{
	}

	void PatientDbSaveDAO::addEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::string("Attempting to add a patient with an ID to database.");
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			systelab::db::ITable& itemsTable = m_db.getTable(db_table::PATIENT);
			auto itemRecord = itemsTable.createRecord();

			auto itemTranslator = m_translatorsFactory.buildPatientTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*itemRecord);
			itemsTable.insertRecord(*itemRecord);

			addAddress();

			transaction->commit();
		}
		catch (std::exception &exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

	void PatientDbSaveDAO::updateEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::string("Attempting to update a patient without id in database.");
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			auto& itemsTable = m_db.getTable(db_table::PATIENT);
			auto itemRecord = itemsTable.createRecord();

			auto itemTranslator = m_translatorsFactory.buildPatientTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*itemRecord);
			itemsTable.updateRecord(*itemRecord);

			updateAddress();

			transaction->commit();
		}
		catch (std::exception &exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

	void PatientDbSaveDAO::deleteEntity()
	{
		if (!m_item.getId().is_initialized())
		{
			throw std::string("Attempting to delete a patient without id in database.");
		}

		std::unique_ptr<dal::ITransactionDAO> transaction;
		try
		{
			transaction = m_daoFactory.startTransaction();

			systelab::db::ITable& table = m_db.getTable(db_table::PATIENT);
			auto record = table.createRecord();
			auto itemTranslator = m_translatorsFactory.buildPatientTranslator(m_item);
			itemTranslator->fillRecordFromEntity(*record);
			table.deleteRecord(*record);

			transaction->commit();
		}
		catch (std::exception &exc)
		{
			transaction->rollback();
			throw exc;
		}
	}

	void PatientDbSaveDAO::addAddress()
	{
		systelab::db::ITable& addressTable = m_db.getTable(db_table::ADDRESS);
		auto addressRecord = addressTable.createRecord();

		std::string patientId = *m_item.getId();
		model::Address& address = m_item.getAddress();
		auto addressTranslator = m_translatorsFactory.buildAddressTranslator(patientId, address);
		addressTranslator->fillRecordFromEntity(*addressRecord);

		addressTable.insertRecord(*addressRecord);
		address.setId(addressRecord->getFieldValue("id").getIntValue());
	}

	void PatientDbSaveDAO::updateAddress()
	{
		systelab::db::ITable& addressTable = m_db.getTable(db_table::ADDRESS);
		auto addressRecord = addressTable.createRecord();

		std::string patientId = *m_item.getId();
		model::Address& address = m_item.getAddress();
		auto addressTranslator = m_translatorsFactory.buildAddressTranslator(patientId, address);
		addressTranslator->fillRecordFromEntity(*addressRecord);

		addressTable.updateRecord(*addressRecord);
	}

}}
