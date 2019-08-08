#include "stdafx.h"
//#include "Utils.h"
//#include "SnowCore/Services/Model/Query/ApplicationVersionQueryService.h"
//
//#include "DbAdapterInterface/IDatabase.h"
//#include "DbSQLiteAdapter/Connection.h"
//#include "DbSQLiteAdapter/ConnectionConfiguration.h"
//
//#include "SecurityConfig/Keys.h"
//
//#include <boost/assign/list_of.hpp>
//
//using namespace testing;
//using testing::_;
//
//namespace snow {	namespace user {	namespace dbtest { 
//		
//		using namespace boost::assign;
//		
//		class ProcessDatabaseTests : public testing::Test
//		{
//		public:
//
//			std::unique_ptr<systelab::db::IDatabase> createDatabase(const std::string& databaseName, const std::string& schemaName, systelab::db::IConnection& connection, std::string sqlFile)
//			{
//				if (boost::filesystem::exists(databaseName))
//				{
//					boost::filesystem::remove(databaseName);
//				}
//				auto key = security::config::keys.find(security::config::USER_DB);
//				systelab::db::sqlite::ConnectionConfiguration dbConfiguration(databaseName, key->second());
//
//				std::unique_ptr<systelab::db::IDatabase> db = connection.loadDatabase(dbConfiguration);
//				std::string defaultDatabaseStatements;
//				readFileToString(schemaName, defaultDatabaseStatements);
//				db->executeMultipleStatements(defaultDatabaseStatements);
//				defaultDatabaseStatements = "";
//				readFileToString(sqlFile, defaultDatabaseStatements);
//				db->executeMultipleStatements(defaultDatabaseStatements);
//				return db;
//			}
//		
//			std::vector<std::string> getFileListFromFolder(const std::string& path, const std::string& filter)
//			{
//				std::vector<std::string> file_list;
//
//				if (!path.empty())
//				{
//					namespace fs = boost::filesystem;
//
//					fs::path apk_path(path);
//					fs::recursive_directory_iterator end;
//
//					for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
//					{
//						const fs::path cp = (*i);
//
//						if (cp.string().find(filter) != std::string::npos)
//						{
//							file_list.push_back(cp.string());
//						}
//					}
//				}
//				return file_list;
//			}
//
//		protected:
//			std::unique_ptr<systelab::db::IDatabase> m_db;
//			systelab::db::sqlite::Connection m_dbConnection;
//		};
//
//		TEST_F(ProcessDatabaseTests, testProcessAllTestUtilitiesSQLFileForUsers)
//		{
//			std::vector<std::string> sqlFilesList = getFileListFromFolder("ProcessDatabaseTests", "users.sql");
//			ASSERT_NO_THROW(createDatabase("ProcessDatabaseTests/users.db", "users_schema.sql", m_dbConnection, sqlFilesList[0]));
//		}
//	}
//}}
//
