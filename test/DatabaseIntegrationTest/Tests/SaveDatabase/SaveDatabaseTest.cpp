#include "stdafx.h"
#include "SaveDatabaseTestData.h"

#include "Tools/Commands/ICommand.h"

#include "DatabaseIntegrationTest/Tests/SaveDatabase/SaveUserScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tests/SaveDatabase/SavePatientScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tools/Core.h"
#include "DatabaseIntegrationTest/Tools/SQLExecutor.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace systelab::test_utility;

namespace seed_cpp { namespace db_test {

	class SaveDatabaseTest : public testing::TestWithParam<SaveDatabaseTestData>
	{
		void SetUp()
		{
			m_databaseFilepath = "./SaveDatabaseTest.db";
			m_sqlExecutor = std::make_unique<SQLExecutor>(m_databaseFilepath);
			m_saveCore = std::make_unique<Core>(m_databaseFilepath);
			m_checkCore = std::make_unique<Core>(m_databaseFilepath);

			m_sqlExecutor->removeDatabaseFile();
			m_sqlExecutor->executeScript("./Database/schema.sql");
		}

		void TearDown()
		{
			m_sqlExecutor->removeDatabaseFile();
		}

	protected:
		std::string m_databaseFilepath;
		std::unique_ptr<SQLExecutor> m_sqlExecutor;
		std::unique_ptr<Core> m_saveCore;
		std::unique_ptr<Core> m_checkCore;
	};


	TEST_P(SaveDatabaseTest, testExecuteCommands)
	{
		m_sqlExecutor->executeScripts(GetParam().getSQLScripts());
		m_saveCore->initialize();

		unsigned int nCommands = (unsigned int) GetParam().getCommandsCount();
		for (unsigned int i = 0; i < nCommands; i++)
		{
			auto& command = GetParam().getCommand(i);
			command.execute(*m_saveCore);
		}

		m_checkCore->initialize();

		auto& expectedModel = m_saveCore->getModel();
		auto& toTestModel = m_checkCore->getModel();
		ASSERT_TRUE(EntityComparator()(expectedModel, toTestModel));
	}

	INSTANTIATE_TEST_CASE_P(SaveUsers, SaveDatabaseTest, ValuesIn(SaveUserScenariosBuilder::build()));
	INSTANTIATE_TEST_CASE_P(SavePatients, SaveDatabaseTest, ValuesIn(SavePatientScenariosBuilder::build()));

}}
