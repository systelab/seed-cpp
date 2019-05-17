#pragma once

#include "Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace db_test {

	class SQLExecutor
	{
	public:
		SQLExecutor(const std::string& dbFilepath);
		virtual ~SQLExecutor();

		bool executeScripts(const std::vector<std::string>&);
		bool executeScript(const std::string&);
		bool executeStatements(const std::string&);

		bool removeDatabaseFile();

	private:
		std::string m_dbFilepath;
	};

}}