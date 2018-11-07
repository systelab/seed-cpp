#pragma once

#include "IDatabaseEntityTranslator.h"


namespace seed_cpp { namespace model {
	class BaseEntity;
}}

namespace seed_cpp { namespace dal {

	class BaseEntityDbTranslator : public IDatabaseEntityTranslator
	{
	public:
		BaseEntityDbTranslator(model::BaseEntity&);
		virtual ~BaseEntityDbTranslator() = default;

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::BaseEntity& m_entity;
	};

}};

