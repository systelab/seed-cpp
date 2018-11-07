#include "StdAfx.h"
#include "BaseEntityDbTranslator.h"

#include "Model/BaseEntity.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"


namespace seed_cpp { namespace dal {

	BaseEntityDbTranslator::BaseEntityDbTranslator(model::BaseEntity& entity)
		:m_entity(entity)
	{
	}

	void BaseEntityDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		std::string id = record.getFieldValue("id").getStringValue();
		boost::posix_time::ptime creationTime = record.getFieldValue("creationTime").getDateTimeValue();
		boost::posix_time::ptime updateTime = record.getFieldValue("updateTime").getDateTimeValue();

		m_entity.setId(id);
		m_entity.setCreationTime(creationTime);
		m_entity.setUpdateTime(updateTime);
	}

	void BaseEntityDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		std::string id = *m_entity.getId();
		boost::posix_time::ptime creationTime = m_entity.getCreationTime();
		boost::posix_time::ptime updateTime = m_entity.getUpdateTime();

		record.getFieldValue("id").setStringValue(id);
		record.getFieldValue("creationTime").setDateTimeValue(creationTime);
		record.getFieldValue("updateTime").setDateTimeValue(updateTime);
	}

}}
