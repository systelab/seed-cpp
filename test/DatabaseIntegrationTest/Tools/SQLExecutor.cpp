#include "stdafx.h"
#include "SQLExecutor.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include <fstream>
#include <stdio.h>
#include <boost/filesystem.hpp>


namespace seed_cpp { namespace db_test {

	SQLExecutor::SQLExecutor(const std::string& dbFilepath)
		:m_dbFilepath(dbFilepath)
	{
	}

	SQLExecutor::~SQLExecutor() = default;

	bool SQLExecutor::executeScripts(const std::vector<std::string>& scripts)
	{
		for (const auto& script : scripts)
		{
			if (!executeScript(script))
			{
				return false;
			}
		}

		return true;
	}

	bool SQLExecutor::executeScript(const std::string& scriptFilepath)
	{
		std::ifstream ifs(scriptFilepath);
		if (!ifs)
		{
			std::cout << "SQLExecutor::executeScript() Unable to find script '"
					  << boost::filesystem::absolute(boost::filesystem::path(scriptFilepath))
					  << std::endl;
			return false;
		}

		std::stringstream ss;
		ss << ifs.rdbuf();
		std::string scriptContents = ss.str();
		ifs.close();

		return executeStatements(scriptContents);
	}

	bool SQLExecutor::executeStatements(const std::string& sqlStatements)
	{
		systelab::db::sqlite::Connection connection;
		systelab::db::sqlite::ConnectionConfiguration configuration(m_dbFilepath);
		auto database = connection.loadDatabase(configuration);

		try
		{
			database->executeMultipleStatements(sqlStatements);
			return true;
		}
		catch (std::exception&)
		{
			return false;
		}
	}

	bool SQLExecutor::removeDatabaseFile()
	{
		std::ifstream ifs(m_dbFilepath.c_str());
		bool dbFileExists = ifs.good();
		ifs.close();

		if (dbFileExists)
		{
			int status = remove(m_dbFilepath.c_str());
			return (status == 0);
		}

		return false;
	}

}}
