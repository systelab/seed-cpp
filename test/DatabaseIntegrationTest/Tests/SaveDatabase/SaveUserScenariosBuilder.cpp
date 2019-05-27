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
			.setUpdateTime(boost::posix_time::from_iso_string("20192105T171400"))
			.getEntity()
		));

		return { scenarioAddUsers };
	}

}}

		// Edit users
//		ModifyDatabaseData
//		(
//			std::string(""),
//			{
//				// Lock password
//				new EditUserCommand(UserDescription(
//					sut::UserBuilder()
//					.setRecordId(7)
//					.setUserName("operator")
//					.setPassword("731628e87e20ed27fc8f1a770bd6c6ed5e7d940f8e4cdba7d8a8568d839fafc5")
//					.setRole(model::User::Role::OPERATOR)
//					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
//					.setUpdateTime(bp::second_clock().local_time())
//					.getEntity()
//				)),
//
//				// Change password and set expiration
//				new EditUserCommand(UserDescription(
//					sut::UserBuilder()
//					.setRecordId(6)
//					.setUserName("manager")
//					.setPassword("40B7475492F07F9E03312E27132CD39546BCFA667E3808C013AFF7EC651830D9")
//					.setRole(model::User::Role::MANAGER)
//					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
//					.setExpirationIntervalDays(30)
//					.setPasswordExpirationDate(bg::day_clock().local_day() + bg::days(30))
//					.setUpdateTime(bp::second_clock().local_time())
//					.getEntity()
//				)),
//
//				// User logged
//				new EditUserCommand(UserDescription(
//					sut::UserBuilder()
//					.setRecordId(2)
//					.setUserName("developer")
//					.setPassword("a69a9b7615fd87c3c50df6a857466fd337fefd0215238fd9e44aeaaa85fbb8cd")
//					.setRole(model::User::Role::DEVELOPER)
//					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
//					.setUpdateTime(bp::second_clock().local_time())
//					.setLastLoginTime(bp::second_clock().local_time())
//					.getEntity()
//				))
//			}
//		),
//
//		// Delete users
//		ModifyDatabaseData
//		(
//			std::string(""),
//			{
//				new DeleteUserCommand(5),
//				new DeleteUserCommand(2)
//			}
//		)
//	};
//
//}}
