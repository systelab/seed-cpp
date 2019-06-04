#include "stdafx.h"
#include "LoadDatabaseTestData.h"

#include "DatabaseIntegrationTest/Tests/LoadDatabase/LoadUserScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tests/LoadDatabase/LoadPatientScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tools/Core.h"
#include "DatabaseIntegrationTest/Tools/SQLExecutor.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace systelab::test_utility;

namespace seed_cpp { namespace db_test {

	class LoadDatabaseTest : public TestWithParam<LoadDatabaseTestData>
	{
	public:
		void SetUp()
		{
			m_databaseFilepath = "./LoadDatabaseTest.db";
			m_sqlExecutor = std::make_unique<SQLExecutor>(m_databaseFilepath);
			m_core = std::make_unique<Core>(m_databaseFilepath);

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
		std::unique_ptr<Core> m_core;
	};

	TEST_P(LoadDatabaseTest, testLoadModelFromDatabase)
	{
		m_sqlExecutor->executeScripts(GetParam().m_sqlScripts);
		m_core->initialize();
		ASSERT_TRUE(EntityComparator()(GetParam().m_expectedModel, m_core->getModel()));
	}

	INSTANTIATE_TEST_CASE_P(LoadUsers, LoadDatabaseTest, ValuesIn(LoadUserScenariosBuilder::build()));
	INSTANTIATE_TEST_CASE_P(LoadPatient, LoadDatabaseTest, ValuesIn(LoadPatientScenariosBuilder::build()));

}}

