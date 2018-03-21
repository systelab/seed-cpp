#pragma once

#include "DAL/DAO/ILoadDAO.h"
#include "Model/EntityMgr.h"


namespace systelab { namespace db {
	class IDatabase;
	class ITableRecord;
}}

namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class IDbTranslatorsFactory;
	class IDatabaseEntityTranslator;

	class PatientDbLoadDAO: public ILoadDAO
	{
	public:
		PatientDbLoadDAO(systelab::db::IDatabase&,
						 model::EntityMgr<model::Patient>&,
						 dal::IDbTranslatorsFactory&);

		void loadAll() const;

	protected:
		void loadPatient(const systelab::db::ITableRecord& src, model::Patient& trg) const;

	private:
		systelab::db::IDatabase& m_db;
		model::EntityMgr<model::Patient>& m_model;
		dal::IDbTranslatorsFactory& m_translatorsFactory;

		void loadAddress(model::Patient&) const;
	};

}}
