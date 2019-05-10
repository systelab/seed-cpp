#include "stdafx.h"
#include "LoadUserScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"

using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadEntityTestData> LoadUserScenariosBuilder::build()
	{
		LoadEntityTestData scenario1;
		scenario1.m_sqlFilename = "LoadUsers.sql";
		scenario1.m_expectedModel =
			ModelBuilder().setUsers({
				model::User(),
				model::User()
			}).getEntity();
			

		std::vector<LoadEntityTestData> scenarios;
		scenarios.push_back(scenario1);

		return scenarios;
	}

	//std::vector<Model> loadUserModels = 
	//{
	//	// Default DB users
	//	ModelDescription
	//	(
	//		std::string(""),
	//		std::vector<UserDescription>
	//		({
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(1)
	//					.setUserName("super")
	//					.setPassword("e11365a8e6ce0e0c02ce3f8408f7d874dbe6102f6456e07ee8d7f2483dd18423")
	//					.setRole(model::User::Role::SUPERUSER)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(2)
	//					.setUserName("developer")
	//					.setPassword("a69a9b7615fd87c3c50df6a857466fd337fefd0215238fd9e44aeaaa85fbb8cd")
	//					.setRole(model::User::Role::DEVELOPER)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(3)
	//					.setUserName("specialist")
	//					.setPassword("7bee5d76c6697f592dc978f04e8ab2fca1d8d9fcaeedced021d68588cdd74716")
	//					.setRole(model::User::Role::SPECIALIST)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(4)
	//					.setUserName("service")
	//					.setPassword("62b74d9aad061493b243b8db4132b917751268fbf5e6c3069d8bf4bd2626b68f")
	//					.setRole(model::User::Role::SERVICE)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(5)
	//					.setUserName("manufacturing")
	//					.setPassword("34575cb0ba8b9613697a8087d2e06f19069c6901c35f7b1a920a8894c08ae652")
	//					.setRole(model::User::Role::MANUFACTURING)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(6)
	//					.setUserName("manager")
	//					.setPassword("ccc4ee191c2ad230e3115191edf2a66ba6e0477a188ee46ebe35a6bd1aabf09f")
	//					.setRole(model::User::Role::MANAGER)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(7)
	//					.setUserName("operator")
	//					.setPassword("731628e87e20ed27fc8f1a770bd6c6ed5e7d940f8e4cdba7d8a8568d839fafc5")
	//					.setRole(model::User::Role::OPERATOR)
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//					.setRecordId(8)
	//					.setUserName("lis")
	//					.setPassword("3659f41a75b1077d2ad479e5c2342e9f899515d934190cd4e6122314a8c29c75")
	//					.setRole(model::User::Role::LIS)
	//				.getEntity()
	//			)
	//		}),
	//		st::EntityComparatorConfiguration({"creationTime"})
	//	),

	//	// Custom DB users
	//	ModelDescription
	//	(
	//		"LoadUsersTest.sql",
	//		std::vector<UserDescription>
	//		({
	//			UserDescription(
	//				sut::UserBuilder()
	//				.setRecordId(1)
	//				.setUserName("TheBoss")
	//				.setPassword("68204CFFACDC5655EAF577C3749C6B17EAFE8DC3ED2DEA3DF2C675EA96B8BF40")
	//				.setRole(model::User::Role::SUPERUSER)
	//				.setExpirationIntervalDays(90)
	//				.setCreationTime(bp::from_iso_string("20190101T012244"))
	//				.setUpdateTime(bp::from_iso_string("20190103T031532"))
	//				.setPasswordExpirationDate(bg::date_from_iso_string("20190401T012244"))
	//				.setLastLoginTime(bp::from_iso_string("20190115T152318"))
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//				.setRecordId(2)
	//				.setUserName("DevMan")
	//				.setPassword("B46FBEA201AA0D76D722CEA5708D3BAE3C4390BDED4BA23B7C4E34E36E536154")
	//				.setRole(model::User::Role::DEVELOPER)
	//				.setExpirationIntervalDays(90)
	//				.setCreationTime(bp::from_iso_string("20190101T013044"))
	//				.setUpdateTime(bp::from_iso_string("20190103T031532"))
	//				.setPasswordExpirationDate(bg::date_from_iso_string("20190401T012244"))
	//				.setLastLoginTime(bp::from_iso_string("20190115T152318"))
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//				.setRecordId(3)
	//				.setUserName("Monger")
	//				.setPassword("40B7475492F07F9E03312E27132CD39546BCFA667E3808C013AFF7EC651830D9")
	//				.setRole(model::User::Role::MANAGER)
	//				.setExpirationIntervalDays(60)
	//				.setCreationTime(bp::from_iso_string("20190104T042244"))
	//				.setUpdateTime(bp::from_iso_string("20190114T031532"))
	//				.setPasswordExpirationDate(bg::date_from_iso_string("20190304T012244"))
	//				.setLastLoginTime(bp::from_iso_string("20190116T152318"))
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//				.setRecordId(4)
	//				.setUserName("OP1")
	//				.setPassword("5FD2C983136F30A54694079DD6D3105986CB51A7906C2F42C50932026595D737")
	//				.setRole(model::User::Role::OPERATOR)
	//				.setExpirationIntervalDays(30)
	//				.setCreationTime(bp::from_iso_string("20190105T012550"))
	//				.setUpdateTime(bp::from_iso_string("20190115T031532"))
	//				.setPasswordExpirationDate(bg::date_from_iso_string("20190205T012244"))
	//				.setLastLoginTime(bp::from_iso_string("20190122T152318"))
	//				.getEntity()
	//			),
	//			UserDescription(
	//				sut::UserBuilder()
	//				.setRecordId(5)
	//				.setUserName("OP2")
	//				.setPassword("87B138C9FB8AFE247690BC34E6D68ECC6A49CAF7060107F8D30EB499656521E3")
	//				.setRole(model::User::Role::OPERATOR)
	//				.setExpirationIntervalDays(30)
	//				.setCreationTime(bp::from_iso_string("20190105T012634"))
	//				.setUpdateTime(bp::from_iso_string("20190115T031532"))
	//				.setPasswordExpirationDate(bg::date_from_iso_string("20190205T012244"))
	//				.setLastLoginTime(bp::from_iso_string("20190118T152318"))
	//				.getEntity()
	//			)
	//		})
	//	)
	//};

}}