#pragma once

#include "DAL/DAO/ILoadDAO.h"
#include "Model/EntityMgr.h"


namespace systelab { namespace db {
	class IDatabase;
	class ITableRecord;
}}

namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace dal {

	class IDbTranslatorsFactory;
	class IDatabaseEntityTranslator;

	class UserDbLoadDAO: public ILoadDAO
	{
	public:
		UserDbLoadDAO(systelab::db::IDatabase&,
					  model::EntityMgr<model::User>&,
					  dal::IDbTranslatorsFactory&);

		void loadAll() const;

	protected:
		void loadUser(const systelab::db::ITableRecord& src, model::User& trg) const;

	private:
		systelab::db::IDatabase& m_db;
		model::EntityMgr<model::User>& m_model;
		dal::IDbTranslatorsFactory& m_translatorsFactory;
	};

}}
