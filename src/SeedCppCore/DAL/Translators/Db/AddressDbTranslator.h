#pragma once

#include "IDatabaseEntityTranslator.h"


namespace seed_cpp { namespace model {
	class Address;
}}

namespace seed_cpp { namespace dal {

	class AddressDbTranslator : public IDatabaseEntityTranslator
	{
	public:
		AddressDbTranslator(model::Address&);
		virtual ~AddressDbTranslator();

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::Address& m_address;
	};

}};

