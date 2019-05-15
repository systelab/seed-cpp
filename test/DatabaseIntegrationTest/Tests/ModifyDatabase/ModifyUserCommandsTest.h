#pragma once

#include "Commands/Users/AddUserCommand.h"
#include "Commands/Users/EditUserCommand.h"
#include "Commands/Users/DeleteUserCommand.h"

#include "Models/ModelDescription.h"
#include "Tests/ModifyDatabase/ModifyDatabaseData.h"

#include "TestUtilities\SnowUser\Builders\UserBuilder.h"

namespace st = snow::test_utility;
namespace sut = snow::user::test_utility;
namespace bp = boost::posix_time;
namespace bg = boost::gregorian;

namespace snow { namespace user { namespace dbtest {

	std::vector<ModifyDatabaseData> modifyUsersData =
	{
		// Add users
		ModifyDatabaseData
		(
			std::string(""),
			{
				new AddUserCommand(UserDescription(
					sut::UserBuilder()
					.setUserName("OP1")
					.setPassword("5FD2C983136F30A54694079DD6D3105986CB51A7906C2F42C50932026595D737")
					.setRole(model::User::Role::OPERATOR)
					.setExpirationIntervalDays(30)
					.setCreationTime(bp::from_iso_string("20190105T012550"))
					.setUpdateTime(bp::from_iso_string("20190115T031532"))
					.setPasswordExpirationDate(bg::date_from_iso_string("20190205T012244"))
					.setLastLoginTime(bp::from_iso_string("20190122T152318"))
					.getEntity()
				)),
				new AddUserCommand(UserDescription(
					sut::UserBuilder()
					.setUserName("DevMan")
					.setPassword("B46FBEA201AA0D76D722CEA5708D3BAE3C4390BDED4BA23B7C4E34E36E536154")
					.setRole(model::User::Role::DEVELOPER)
					.setExpirationIntervalDays(90)
					.setCreationTime(bp::from_iso_string("20190101T013044"))
					.setUpdateTime(bp::from_iso_string("20190103T031532"))
					.setPasswordExpirationDate(bg::date_from_iso_string("20190401T012244"))
					.setLastLoginTime(bp::from_iso_string("20190115T152318"))
					.getEntity()
				)),
				// Not mandatory fields set to NULL
				new AddUserCommand(UserDescription(
					sut::UserBuilder()
					.setUserName("SuperDevMan")
					.setPassword("B46FBEA201AA0D76D722CEA5708D3BAE3C4390BDED4BA23B7C4E34E36E536154")
					.setRole(model::User::Role::DEVELOPER)
					.setCreationTime(bp::from_iso_string("20190101T013044"))
					.setUpdateTime(bp::from_iso_string("20190103T031532"))
					.getEntity()
				))
			}
		),

		// Edit users
		ModifyDatabaseData
		(
			std::string(""),
			{
				// Lock password
				new EditUserCommand(UserDescription(
					sut::UserBuilder()
					.setRecordId(7)
					.setUserName("operator")
					.setPassword("731628e87e20ed27fc8f1a770bd6c6ed5e7d940f8e4cdba7d8a8568d839fafc5")
					.setRole(model::User::Role::OPERATOR)
					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
					.setUpdateTime(bp::second_clock().local_time())
					.getEntity()
				)),

				// Change password and set expiration
				new EditUserCommand(UserDescription(
					sut::UserBuilder()
					.setRecordId(6)
					.setUserName("manager")
					.setPassword("40B7475492F07F9E03312E27132CD39546BCFA667E3808C013AFF7EC651830D9")
					.setRole(model::User::Role::MANAGER)
					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
					.setExpirationIntervalDays(30)
					.setPasswordExpirationDate(bg::day_clock().local_day() + bg::days(30))
					.setUpdateTime(bp::second_clock().local_time())
					.getEntity()
				)),

				// User logged
				new EditUserCommand(UserDescription(
					sut::UserBuilder()
					.setRecordId(2)
					.setUserName("developer")
					.setPassword("a69a9b7615fd87c3c50df6a857466fd337fefd0215238fd9e44aeaaa85fbb8cd")
					.setRole(model::User::Role::DEVELOPER)
					.setCreationTime(bp::from_iso_string("20190101T013044")) // Can't be null
					.setUpdateTime(bp::second_clock().local_time())
					.setLastLoginTime(bp::second_clock().local_time())
					.getEntity()
				))
			}
		),

		// Delete users
		ModifyDatabaseData
		(
			std::string(""),
			{
				new DeleteUserCommand(5),
				new DeleteUserCommand(2)
			}
		)
	};

}}}