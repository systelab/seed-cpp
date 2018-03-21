#pragma once

#include "IDatabaseEntityTranslator.h"


namespace seed_cpp { namespace model {
	class Address;
}}

namespace seed_cpp { namespace dal {

	class AddressDbTranslator : public IDatabaseEntityTranslator
	{
	public:
		AddressDbTranslator(unsigned int patientId, model::Address&);
		virtual ~AddressDbTranslator();

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		unsigned int m_patientId;
		model::Address& m_address;
	};

}};

