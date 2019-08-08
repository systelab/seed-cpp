#include "stdafx.h"
#include "SaveUserScenariosBuilder.h"

#include "Tools/Commands/Users/AddUserCommand.h"
#include "Tools/Commands/Users/EditUserCommand.h"
#include "Tools/Commands/Users/DeleteUserCommand.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<SaveDatabaseTestData> SaveUserScenariosBuilder::build()
	{
		// Add some users
		SaveDatabaseTestData scenarioAddUsers;
		scenarioAddUsers.setSQLScripts({});
		scenarioAddUsers.addCommand(std::make_unique<AddUserCommand>(
			UserBuilder()
				.setId(std::string("B08BFF46-6AA8-4558-9CD5-0B6EB8C4B768"))
				.setName("Phil").setSurname("Collins")
				.setLogin("pcollins").setRole(model::User::ADMIN_ROLE)
				.setPassword("LeavingNewYorkNeverEasy")
				.setCreationTime(boost::posix_time::from_iso_string("20150405T112133"))
				.setUpdateTime(boost::posix_time::from_iso_string("20190523T220314"))
			.getEntity()
		));
		scenarioAddUsers.addCommand(std::make_unique<AddUserCommand>(
			UserBuilder()
				.setId(std::string("8294FCCD-4532-4DE5-9DEB-BF81C48378BC"))
				.setName("Paco").setSurname("Perez Garcia")
				.setLogin("pperez").setRole(model::User::USER_ROLE)
				.setPassword("PepeKiko99")
				.setCreationTime(boost::posix_time::from_iso_string("20180923T130000"))
				.setUpdateTime(boost::posix_time::from_iso_string("20190521T171400"))
			.getEntity()
		));

		// Edit an existing user
		SaveDatabaseTestData scenarioEditUser;
		scenarioEditUser.setSQLScripts({ "Database/Users/AdminUser.sql" });
		scenarioEditUser.addCommand(std::make_unique<EditUserCommand>(
			UserBuilder()
				.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
				.setName("Peter").setSurname("Collins")
				.setLogin("pcollins").setRole(model::User::ADMIN_ROLE)
				.setPassword("PasswordHasBeenChanged")
				.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
				.setUpdateTime(boost::posix_time::from_iso_string("20200212T093045"))
			.getEntity()
		));

		// Delete existing users
		SaveDatabaseTestData scenarioDeleteUsers;
		scenarioDeleteUsers.setSQLScripts({ "Database/Users/AdminUser.sql", "Database/Users/BasicUsers.sql" });
		scenarioDeleteUsers.addCommand(std::make_unique<DeleteUserCommand>("73A800FC-621C-4D94-A1A4-0B39075458D4"));
		scenarioDeleteUsers.addCommand(std::make_unique<DeleteUserCommand>("9055B141-3307-4868-9C81-D5722A5DC16C"));

		// Complex scenario
		SaveDatabaseTestData scenarioComplex;
		scenarioComplex.setSQLScripts({ "Database/Users/AdminUser.sql", "Database/Users/BasicUsers.sql" });
		scenarioComplex.addCommand(std::make_unique<DeleteUserCommand>("73A800FC-621C-4D94-A1A4-0B39075458D4"));
		scenarioComplex.addCommand(std::make_unique<AddUserCommand>(
			UserBuilder()
				.setId(std::string("BD064A6D-45A6-43CE-9C15-5CBDC8DA9C4C"))
				.setName("Jaime").setSurname("Duckworth")
				.setLogin("jduckworth").setRole(model::User::USER_ROLE)
				.setPassword("PasswordDuckworth")
				.setCreationTime(boost::posix_time::from_iso_string("20180101T010100"))
				.setUpdateTime(boost::posix_time::from_iso_string("20180101T010100"))
			.getEntity()
		));
		scenarioComplex.addCommand(std::make_unique<EditUserCommand>(
			UserBuilder()
				.setId(std::string("4DBF18D0-689B-4974-B727-5CA503709E8E"))
				.setName("Peter").setSurname("Collins")
				.setLogin("pcollins").setRole(model::User::ADMIN_ROLE)
				.setPassword("PasswordHasBeenChanged")
				.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
				.setUpdateTime(boost::posix_time::from_iso_string("20200212T093045"))
			.getEntity()
		));

		return { scenarioAddUsers, scenarioEditUser, scenarioDeleteUsers, scenarioComplex };
	}

}}

