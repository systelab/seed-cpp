#include "stdafx.h"
#include "SQLExecutor.h"

#include <fstream>
#include <sqlite3.h>
#include <stdio.h>


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
			return false;
		}

		std::string scriptContents;
		ifs.seekg(0, std::ios::end);
		scriptContents.resize(static_cast<unsigned int>(ifs.tellg()));
		ifs.seekg(0, std::ios::beg);
		ifs.read(&scriptContents[0], scriptContents.size());
		ifs.close();

		return executeStatements(scriptContents);
	}

	bool SQLExecutor::executeStatements(const std::string& sqlStatements)
	{
		sqlite3* db = NULL;
		int openResult = sqlite3_open(m_dbFilepath.c_str(), &db);
		if (openResult != SQLITE_OK)
		{
			return false;
		}

		int execResult = sqlite3_exec(db, sqlStatements.c_str(), NULL, NULL, NULL);
		if (execResult != SQLITE_OK)
		{
			sqlite3_close(db);
			return false;
		}

		int closeResult = sqlite3_close(db);
		if (closeResult != SQLITE_OK)
		{
			return false;
		}

		return true;
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
