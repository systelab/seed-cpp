#pragma once

#include "BaseEntityDbTranslator.h"

namespace seed_cpp { namespace model {
	class Allergy;
}}

namespace seed_cpp { namespace dal {

	class AllergyDbTranslator : public BaseEntityDbTranslator
	{
	public:
		AllergyDbTranslator(model::Allergy&);
		virtual ~AllergyDbTranslator();

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::Allergy& m_entity;
	};

}}