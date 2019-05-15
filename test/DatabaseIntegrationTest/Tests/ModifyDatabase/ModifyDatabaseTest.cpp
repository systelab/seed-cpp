#include "stdafx.h"
//#include "DatabaseContext.h"
//
//#include "Commands/ModelCommand.h"
//#include "Models/ModelComparator.h"
//#include "SecurityConfig/Keys.h"
//
//#include "Tests/ModifyDatabase/ModifyDatabaseData.h"
//#include "Tests/ModifyDatabase/ModifyUserCommandsTest.h"
//
//
//namespace snow { namespace user { namespace dbtest {
//
//	class ModifyDatabaseTest: public testing::TestWithParam<ModifyDatabaseData>
//	{
//		
//	protected:
//		DatabaseContext m_context;
//	};
//	
//	TEST_P(ModifyDatabaseTest, testExecuteCommands)
//	{
//		const ModifyDatabaseData& data = GetParam();
//
//		if (data.m_initialDBFilename.size())
//		{
//			m_context.loadSQLFile(data.m_initialDBFilename);
//		}
//
//		for (auto it = data.m_commands.begin(); it != data.m_commands.end(); ++it)
//		{
//			(*it)->runCommand(m_context.getModuleContext());
//		}
//
//		DatabaseContext newContext(false);
//		ModelComparator::compareModels(m_context.getModel(), newContext.getModel());
//	}
//	
//	INSTANTIATE_TEST_CASE_P(ModifyUsers, ModifyDatabaseTest, testing::ValuesIn(modifyUsersData));
//
//}}}