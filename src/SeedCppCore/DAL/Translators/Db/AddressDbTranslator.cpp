#include "StdAfx.h"
#include "AddressDbTranslator.h"

#include "Model/Address.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"


namespace seed_cpp { namespace dal {

	AddressDbTranslator::AddressDbTranslator(model::Address& address)
		:m_address(address)
	{
	}

	AddressDbTranslator::~AddressDbTranslator()
	{
	}

	void AddressDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		unsigned int id = record.getFieldValue("id").getIntValue();
		unsigned int patientId = record.getFieldValue("patientId").getIntValue();
		std::string coordinates = record.getFieldValue("coordinates").getStringValue();
		std::string street = record.getFieldValue("street").getStringValue();
		std::string city = record.getFieldValue("city").getStringValue();
		std::string zip = record.getFieldValue("zip").getStringValue();

		m_address.setId(id);
		m_address.setPatientId(patientId);
		m_address.setCoordinates(coordinates);
		m_address.setStreet(street);
		m_address.setCity(city);
		m_address.setZip(zip);
	}

	void AddressDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		boost::optional<unsigned int> id = m_address.getId();
		if (id)
		{
			record.getFieldValue("id").setIntValue((int) *id);
		}
		else
		{
			record.getFieldValue("id").setDefault();
		}

		unsigned int patientId = *m_address.getPatientId();
		std::string coordinates = m_address.getCoordinates();
		std::string street = m_address.getStreet();
		std::string city = m_address.getCity();
		std::string zip = m_address.getZip();

		record.getFieldValue("patientId").setIntValue(patientId);
		record.getFieldValue("coordinates").setStringValue(coordinates);
		record.getFieldValue("street").setStringValue(street);
		record.getFieldValue("city").setStringValue(city);
		record.getFieldValue("zip").setStringValue(zip);
	}

}}
