#include "stdafx.h"

#include "Tools/Commands/ICommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"
#include "DatabaseIntegrationTest/Tools/SQLExecutor.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;

namespace seed_cpp { namespace db_test {

	struct ProcessDatabaseTestData
	{
		std::string name;
		std::vector<std::string> scripts;
	};

	namespace {
		std::vector<ProcessDatabaseTestData> testData =
		{
			{ "Complete", {"Database/Complete/Complete.sql"} }
		};
	}

	class ProcessDatabaseTest : public TestWithParam<ProcessDatabaseTestData>
	{
	public:
		void SetUp()
		{
			m_databaseFilepath = "./" + GetParam().name + ".db";
			m_sqlExecutor = std::make_unique<SQLExecutor>(m_databaseFilepath);
			m_core = std::make_unique<Core>(m_databaseFilepath);

			m_sqlExecutor->removeDatabaseFile();
			m_sqlExecutor->executeScript("./Database/schema.sql");
		}

	protected:
		std::string m_databaseFilepath;
		std::unique_ptr<SQLExecutor> m_sqlExecutor;
		std::unique_ptr<Core> m_core;
	};

	TEST_P(ProcessDatabaseTest, testProcessAllTestUtilitiesSQLFileForUsers)
	{
		ASSERT_NO_THROW(m_sqlExecutor->executeScripts(GetParam().scripts));
		ASSERT_NO_THROW(m_core->initialize());
	}

	INSTANTIATE_TEST_CASE_P(ProcessDatabase, ProcessDatabaseTest, ValuesIn(testData));

}}

