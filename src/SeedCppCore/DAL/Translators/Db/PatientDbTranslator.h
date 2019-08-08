#pragma once

#include "SeedCppCore/DAL/Translators/Db/BaseEntityDbTranslator.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class PatientDbTranslator : public BaseEntityDbTranslator
	{
	public:
		PatientDbTranslator(model::Patient&);
		virtual ~PatientDbTranslator() = default;

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::Patient& m_patient;
	};

}};

