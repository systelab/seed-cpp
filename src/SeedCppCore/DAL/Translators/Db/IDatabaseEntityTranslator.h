#pragma once

namespace systelab { namespace db {
	class IDatabase;
	class ITableRecord;
	class ITable;
}}

namespace seed_cpp { namespace dal {

	class IDatabaseDAOFactory;

	class IDatabaseEntityTranslator
	{
	public:
		virtual ~IDatabaseEntityTranslator(){};

		virtual void fillEntityFromRecord(const systelab::db::ITableRecord&) = 0;
		virtual void fillRecordFromEntity(systelab::db::ITableRecord&) const = 0;
	};

}}
