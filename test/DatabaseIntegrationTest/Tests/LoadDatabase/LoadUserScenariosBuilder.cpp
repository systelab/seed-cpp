#include "stdafx.h"
#include "LoadUserScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadDatabaseTestData> LoadUserScenariosBuilder::build()
	{
		// Admin user
		LoadDatabaseTestData scenarioAdminUser;
		scenarioAdminUser.m_sqlScripts = { "Database/Users/AdminUser.sql" };
		scenarioAdminUser.m_expectedModel =
			ModelBuilder().setUsers({
				UserBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
					.setName("John").setSurname("Smith")
					.setLogin("jsmith").setRole(model::User::ADMIN_ROLE)
					.setPassword("P@assw0rd")
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.getEntity(),
			}).getEntity();

		// Basic users
		LoadDatabaseTestData scenarioBasicUsers;
		scenarioBasicUsers.m_sqlScripts = { "Database/Users/BasicUsers.sql" };
		scenarioBasicUsers.m_expectedModel =
			ModelBuilder().setUsers({
				UserBuilder()
					.setId(std::string("9055B141-3307-4868-9C81-D5722A5DC16C"))
					.setName("Peter").setSurname("Parker")
					.setLogin("pparker").setRole(model::User::USER_ROLE)
					.setPassword("SuperSecret!")
					.setCreationTime(boost::posix_time::from_iso_string("20180101T102030"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.getEntity(),
				UserBuilder()
					.setId(std::string("4DBF18D0-689B-4974-B727-5CA503709E8E"))
					.setName("Kevin").setSurname("Robinson")
					.setLogin("krobinson").setRole(model::User::USER_ROLE)
					.setPassword("Ph2d3ghI7h")
					.setCreationTime(boost::posix_time::from_iso_string("20180724T184500"))
					.setUpdateTime(boost::posix_time::from_iso_string("20191213T235959"))
					.getEntity(),
			}).getEntity();

		// Admin and basic users
		LoadDatabaseTestData scenarioAdminAndBasicUsers;
		scenarioAdminAndBasicUsers.m_sqlScripts = { "Database/Users/AdminUser.sql",
													"Database/Users/BasicUsers.sql" };
		scenarioAdminAndBasicUsers.m_expectedModel =
			ModelBuilder().setUsers({
				UserBuilder()
					.setId(std::string("9055B141-3307-4868-9C81-D5722A5DC16C"))
					.setName("Peter").setSurname("Parker")
					.setLogin("pparker").setRole(model::User::USER_ROLE)
					.setPassword("SuperSecret!")
					.setCreationTime(boost::posix_time::from_iso_string("20180101T102030"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.getEntity(),
				UserBuilder()
					.setId(std::string("4DBF18D0-689B-4974-B727-5CA503709E8E"))
					.setName("Kevin").setSurname("Robinson")
					.setLogin("krobinson").setRole(model::User::USER_ROLE)
					.setPassword("Ph2d3ghI7h")
					.setCreationTime(boost::posix_time::from_iso_string("20180724T184500"))
					.setUpdateTime(boost::posix_time::from_iso_string("20191213T235959"))
					.getEntity(),
				UserBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
					.setName("John").setSurname("Smith")
					.setLogin("jsmith").setRole(model::User::ADMIN_ROLE)
					.setPassword("P@assw0rd")
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.getEntity()
			}).getEntity();

		return { scenarioAdminUser, scenarioBasicUsers, scenarioAdminAndBasicUsers };
	}

}}