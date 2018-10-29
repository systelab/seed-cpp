#include "StdAfx.h"
#include "PatientDbLoadDAO.h"

#include "DAL/Translators/Db/IDatabaseEntityTranslator.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "Model/Address.h"
#include "Model/Patient.h"

#include "DbAdapterInterface/IDatabase.h"
#include "DbAdapterInterface/IFieldValue.h"
#include "DbAdapterInterface/ITable.h"
#include "DbAdapterInterface/ITableRecord.h"


namespace seed_cpp { namespace dal {

	PatientDbLoadDAO::PatientDbLoadDAO(systelab::db::IDatabase& db,
									   model::EntityMgr<model::Patient>& model,
									   dal::IDbTranslatorsFactory& translatorsFactory)
		:m_db(db)
		,m_model(model)
		,m_translatorsFactory(translatorsFactory)
	{
	}

	void PatientDbLoadDAO::loadAll() const
	{
		std::vector< std::unique_ptr<model::Patient> > items;
		systelab::db::ITable& itemsTable = m_db.getTable("Patient");
		std::unique_ptr<systelab::db::ITableRecordSet> itemsRecordset = itemsTable.getAllRecords();
		while (itemsRecordset->isCurrentRecordValid())
		{
			const systelab::db::ITableRecord& itemRecord = itemsRecordset->getCurrentRecord();

			std::unique_ptr<model::Patient> newItem(new model::Patient());
			loadPatient(itemRecord, *newItem);
			items.push_back(std::move(newItem) );

			itemsRecordset->nextRecord();
		}

		m_model.setEntities(std::move(items));
	}

	void PatientDbLoadDAO::loadPatient(const systelab::db::ITableRecord& src, model::Patient& patient) const
	{
		namespace sdb = systelab::db;
		std::unique_ptr<IDatabaseEntityTranslator> translator = m_translatorsFactory.buildPatientTranslator(patient);
		translator->fillEntityFromRecord(src);

		loadAddress(patient);
	}

	void PatientDbLoadDAO::loadAddress(model::Patient& patient) const
	{
		namespace sdb = systelab::db;

		std::string patientId = *patient.getId();
		systelab::db::ITable& table = m_db.getTable("Address");
		std::unique_ptr<sdb::IFieldValue> patientIdFieldValue = table.createFieldValue(table.getField("id"), patientId);
		std::unique_ptr<sdb::ITableRecordSet> addressRecordset = table.filterRecordsByField(*patientIdFieldValue);
		if (addressRecordset->isCurrentRecordValid())
		{
			const sdb::ITableRecord& addressRecord = addressRecordset->getCurrentRecord();
			std::unique_ptr<IDatabaseEntityTranslator> addressTranslator = m_translatorsFactory.buildAddressTranslator(patientId, patient.getAddress());
			addressTranslator->fillEntityFromRecord(addressRecord);
		}
	}

}}