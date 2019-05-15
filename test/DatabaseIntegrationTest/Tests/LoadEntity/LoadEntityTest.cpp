#include "stdafx.h"
#include "LoadEntityTestData.h"

#include "DatabaseIntegrationTest/Tests/LoadEntity/LoadUserScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tools/Core.h"
#include "DatabaseIntegrationTest/Tools/SQLExecutor.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace systelab::test_utility;

namespace seed_cpp { namespace db_test {

	class LoadEntityTest : public TestWithParam<LoadEntityTestData>
	{
	public:
		void SetUp()
		{
			m_databaseFilepath = "./LoadEntityTest.db";
			m_sqlExecutor = std::make_unique<SQLExecutor>(m_databaseFilepath);
			m_core = std::make_unique<Core>(m_databaseFilepath);
		}

	protected:
		std::string m_databaseFilepath;
		std::unique_ptr<SQLExecutor> m_sqlExecutor;
		std::unique_ptr<Core> m_core;
	};

	TEST_P(LoadEntityTest, testLoadEntities)
	{
		m_sqlExecutor->executeScript("./Database/schema.sql");
		m_sqlExecutor->executeScripts(GetParam().m_sqlScripts);
		m_core->initialize();
		ASSERT_TRUE(EntityComparator()(GetParam().m_expectedModel, m_core->getModel()));
	}

	INSTANTIATE_TEST_CASE_P(LoadUsers,	LoadEntityTest, ValuesIn(LoadUserScenariosBuilder::build()));

}}

