#pragma once

#include "IDatabaseEntityTranslator.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace dal {

	class UserDbTranslator : public IDatabaseEntityTranslator
	{
	public:
		UserDbTranslator(model::User&);
		virtual ~UserDbTranslator();

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::User& m_user;
	};

}};

