#include "stdafx.h"
#include "AllergyDbTranslator.h"

#include "Model/Allergy.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"

namespace seed_cpp { namespace dal {

	AllergyDbTranslator::AllergyDbTranslator(model::Allergy& entity)
		:BaseEntityDbTranslator(entity)
		,m_entity(entity)
	{
	}

	AllergyDbTranslator::~AllergyDbTranslator() = default;

	void AllergyDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		BaseEntityDbTranslator::fillEntityFromRecord(record);

		std::string name		= record.getFieldValue("name").getStringValue();
		std::string signs		= record.getFieldValue("signs").getStringValue();
		std::string symptoms	= record.getFieldValue("symptoms").getStringValue();

		m_entity.setName(name);
		m_entity.setSigns(signs);
		m_entity.setSymptoms(symptoms);
	}

	void AllergyDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		BaseEntityDbTranslator::fillRecordFromEntity(record);

		std::string name		= m_entity.getName();
		std::string signs		= m_entity.getSigns();
		std::string symptoms	= m_entity.getSymptoms();

		record.getFieldValue("name").setStringValue(name);
		record.getFieldValue("signs").setStringValue(signs);
		record.getFieldValue("symptoms").setStringValue(symptoms);
	}

}}