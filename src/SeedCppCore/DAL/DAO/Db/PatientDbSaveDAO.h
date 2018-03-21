#pragma once

#include "DAL/DAO/ISaveDAO.h"


namespace systelab { namespace db {
	class IDatabase;
	class ITable;
}}

namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class IDbDAOFactory;
	class IDbTranslatorsFactory;

	class PatientDbSaveDAO : public ISaveDAO
	{
	public:
		PatientDbSaveDAO(systelab::db::IDatabase&,
						 model::Patient&,
						 dal::IDbDAOFactory&,
						 dal::IDbTranslatorsFactory&);

		void addEntity();
		void updateEntity();
		void deleteEntity();

	private:
		void addAddress();
		void updateAddress();

	private:
		systelab::db::IDatabase& m_db;
		model::Patient& m_item;
		dal::IDbDAOFactory& m_daoFactory;
		dal::IDbTranslatorsFactory& m_translatorsFactory;
	};

}}

