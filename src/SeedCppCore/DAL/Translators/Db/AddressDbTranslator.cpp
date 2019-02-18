#include "AddressDbTranslator.h"

#include "Model/Address.h"

#include "ITableRecord.h"
#include "IFieldValue.h"


namespace seed_cpp { namespace dal {

	AddressDbTranslator::AddressDbTranslator(const std::string& patientId,
											 model::Address& address)
		:m_patientId(patientId)
		,m_address(address)
	{
	}

	AddressDbTranslator::~AddressDbTranslator()
	{
	}

	void AddressDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		unsigned int id = record.getFieldValue("id").getIntValue();
		std::string coordinates = record.getFieldValue("coordinates").getStringValue();
		std::string street = record.getFieldValue("street").getStringValue();
		std::string city = record.getFieldValue("city").getStringValue();
		std::string zip = record.getFieldValue("zip").getStringValue();

		m_address.setId(id);
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
			record.getFieldValue("id").setIntValue(*id);
		}
		else
		{
			record.getFieldValue("id").setDefault();
		}

		std::string coordinates = m_address.getCoordinates();
		std::string street = m_address.getStreet();
		std::string city = m_address.getCity();
		std::string zip = m_address.getZip();

		record.getFieldValue("patientId").setStringValue(m_patientId);
		record.getFieldValue("coordinates").setStringValue(coordinates);
		record.getFieldValue("street").setStringValue(street);
		record.getFieldValue("city").setStringValue(city);
		record.getFieldValue("zip").setStringValue(zip);
	}

}}
