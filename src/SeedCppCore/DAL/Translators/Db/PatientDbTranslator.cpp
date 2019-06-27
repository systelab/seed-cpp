#include "stdafx.h"
#include "PatientDbTranslator.h"

#include "Model/Patient.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"


namespace seed_cpp { namespace dal {

	PatientDbTranslator::PatientDbTranslator(model::Patient& patient)
		:BaseEntityDbTranslator(patient)
		,m_patient(patient)
	{
	}

	void PatientDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		BaseEntityDbTranslator::fillEntityFromRecord(record);

		std::string name = record.getFieldValue("name").getStringValue();
		m_patient.setName(name);

		std::string surname = record.getFieldValue("surname").getStringValue();
		m_patient.setSurname(surname);

		if (record.getFieldValue("dob").isNull())
		{
			m_patient.setDob(boost::none);
		}
		else
		{
			boost::posix_time::ptime dob = record.getFieldValue("dob").getDateTimeValue();
			m_patient.setDob(dob);
		}

		std::string email = record.getFieldValue("email").getStringValue();
		m_patient.setEmail(email);
	}

	void PatientDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		BaseEntityDbTranslator::fillRecordFromEntity(record);

		std::string name = m_patient.getName();
		record.getFieldValue("name").setStringValue(name);

		std::string surname = m_patient.getSurname();
		record.getFieldValue("surname").setStringValue(surname);

		auto dob = m_patient.getDob();
		if (dob)
		{
			record.getFieldValue("dob").setDateTimeValue(*dob);
		}
		else
		{
			record.getFieldValue("dob").setNull();
		}

		std::string email = m_patient.getEmail();
		record.getFieldValue("email").setStringValue(email);
	}

}}
