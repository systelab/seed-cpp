#pragma once

#include "IDatabaseEntityTranslator.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class PatientDbTranslator : public IDatabaseEntityTranslator
	{
	public:
		PatientDbTranslator(model::Patient&);
		virtual ~PatientDbTranslator();

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::Patient& m_patient;
	};

}};

