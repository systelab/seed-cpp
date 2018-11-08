#include "StdAfx.h"
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
		std::string surname = record.getFieldValue("surname").getStringValue();
		boost::posix_time::ptime dob = record.getFieldValue("dob").getDateTimeValue();
		std::string email = record.getFieldValue("email").getStringValue();

		m_patient.setName(name);
		m_patient.setSurname(surname);
		m_patient.setDob(dob);
		m_patient.setEmail(email);
	}

	void PatientDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		BaseEntityDbTranslator::fillRecordFromEntity(record);

		std::string name = m_patient.getName();
		std::string surname = m_patient.getSurname();
		boost::posix_time::ptime dob = m_patient.getDob();
		std::string email = m_patient.getEmail();

		record.getFieldValue("name").setStringValue(name);
		record.getFieldValue("surname").setStringValue(surname);
		record.getFieldValue("dob").setDateTimeValue(dob);
		record.getFieldValue("email").setStringValue(email);
	}

}}
