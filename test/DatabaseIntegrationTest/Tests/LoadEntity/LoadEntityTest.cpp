#include "stdafx.h"
#include "LoadEntityTestData.h"

#include "DatabaseIntegrationTest/Tests/LoadEntity/LoadUserScenariosBuilder.h"
#include "DatabaseIntegrationTest/Tools/Context.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace systelab::test_utility;

namespace seed_cpp { namespace db_test {

	class LoadEntityTest : public TestWithParam<LoadEntityTestData>
	{
	public:
		void SetUp()
		{
			m_databaseFilepath = "LoadEntityTest.db";
			m_context = std::make_unique<Context>(m_databaseFilepath);
		}

		void loadSQLFile(const std::string& filepath)
		{

		}

	protected:
		std::string m_databaseFilepath;
		std::unique_ptr<Context> m_context;
	};

	TEST_P(LoadEntityTest, testLoadEntities)
	{
		loadSQLFile(GetParam().m_sqlFilename);
		m_context->initialize();
		ASSERT_TRUE(EntityComparator()(GetParam().m_expectedModel, m_context->getModel()));
	}

	INSTANTIATE_TEST_CASE_P(LoadUsers,	LoadEntityTest, ValuesIn(LoadUserScenariosBuilder::build()));

}}

