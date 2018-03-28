#pragma once

#include "DAL/DAO/ISaveDAO.h"


namespace systelab { namespace db {
	class IDatabase;
	class ITable;
}}

namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace dal {

	class IDbDAOFactory;
	class IDbTranslatorsFactory;

	class UserDbSaveDAO : public ISaveDAO
	{
	public:
		UserDbSaveDAO(systelab::db::IDatabase&,
					  model::User&,
					  dal::IDbDAOFactory&,
					  dal::IDbTranslatorsFactory&);

		void addEntity();
		void updateEntity();
		void deleteEntity();

	private:
		systelab::db::IDatabase& m_db;
		model::User& m_item;
		dal::IDbDAOFactory& m_daoFactory;
		dal::IDbTranslatorsFactory& m_translatorsFactory;
	};

}}

