#pragma once

#include "SeedCppCore/DAL/Translators/Db/BaseEntityDbTranslator.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace dal {

	class UserDbTranslator : public BaseEntityDbTranslator
	{
	public:
		UserDbTranslator(model::User&);
		virtual ~UserDbTranslator() = default;

		void fillEntityFromRecord(const systelab::db::ITableRecord&);
		void fillRecordFromEntity(systelab::db::ITableRecord&) const;

	private:
		model::User& m_user;
	};

}};

