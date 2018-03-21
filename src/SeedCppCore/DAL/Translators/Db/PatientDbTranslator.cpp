#include "StdAfx.h"
#include "PatientDbTranslator.h"

#include "Model/Patient.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"


namespace seed_cpp { namespace dal {

	PatientDbTranslator::PatientDbTranslator(model::Patient& patient)
		:m_patient(patient)
	{
	}

	PatientDbTranslator::~PatientDbTranslator()
	{
	}

	void PatientDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		unsigned int id = record.getFieldValue("id").getIntValue();
		std::string name = record.getFieldValue("name").getStringValue();
		std::string surname = record.getFieldValue("surname").getStringValue();
		boost::posix_time::ptime dob = record.getFieldValue("dob").getDateTimeValue();
		std::string email = record.getFieldValue("email").getStringValue();

		m_patient.setId(id);
		m_patient.setName(name);
		m_patient.setSurname(surname);
		m_patient.setDob(dob);
		m_patient.setEmail(email);
	}

	void PatientDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		boost::optional<unsigned int> id = m_patient.getId();
		if (id)
		{
			record.getFieldValue("id").setIntValue((int) *id);
		}
		else
		{
			record.getFieldValue("id").setDefault();
		}

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
