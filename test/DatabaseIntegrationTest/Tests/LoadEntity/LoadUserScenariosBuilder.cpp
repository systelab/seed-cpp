#include "stdafx.h"
#include "LoadUserScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"

using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadEntityTestData> LoadUserScenariosBuilder::build()
	{
		// No users / Default user
		LoadEntityTestData scenarioNoUsers;
		scenarioNoUsers.m_sqlScripts = {};
		scenarioNoUsers.m_expectedModel =
			ModelBuilder().setUsers({
				UserBuilder()
					.setLogin("Systelab").setRole(model::User::ADMIN_ROLE)
					.setName("Systelab").setSurname("Systelab")
					.setPassword("5FD2C983136F30A54694079DD6D3105986CB51A7906C2F42C50932026595D737")
					.getEntity(),
			}).getEntity();

		// Single user
		LoadEntityTestData scenarioSingleUser;
		scenarioSingleUser.m_sqlScripts = { "LoadSingleUser.sql" };
		scenarioSingleUser.m_expectedModel = 
			ModelBuilder().setUsers({
				UserBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
					.setLogin("pparker").setRole(model::User::ADMIN_ROLE)
					.setName("Peter").setSurname("Parker")
					.setPassword("5FD2C983136F30A54694079DD6D3105986CB51A7906C2F42C50932026595D737")
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
					.setUpdateTime(boost::posix_time::from_iso_string("20170312T142500"))
					.getEntity(),
			}).getEntity();

		// Some users
		LoadEntityTestData scenarioSomeUsers;
		scenarioSomeUsers.m_sqlScripts = { "LoadSomeUsers.sql" };
		scenarioSomeUsers.m_expectedModel =
			ModelBuilder().setUsers({
				UserBuilder()
					.setId(std::string("9055B141-3307-4868-9C81-D5722A5DC16C"))
					.setLogin("Systelab").setRole(model::User::ADMIN_ROLE)
					.setName("Default").setSurname("Corporative User")
					.setPassword("68204CFFACDC5655EAF577C3749C6B17EAFE8DC3ED2DEA3DF2C675EA96B8BF40")
					.setCreationTime(boost::posix_time::from_iso_string("20190101T012244"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190101T012244"))
					.getEntity(),
				UserBuilder()
					.setId(std::string("4DBF18D0-689B-4974-B727-5CA503709E8E"))
					.setLogin("jsmith23").setRole(model::User::USER_ROLE)
					.setName("John").setSurname("Smith")
					.setPassword("B46FBEA201AA0D76D722CEA5708D3BAE3C4390BDED4BA23B7C4E34E36E536154")
					.setCreationTime(boost::posix_time::from_iso_string("20190103T031532"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190101T012244"))
					.getEntity(),
			}).getEntity();

		return { scenarioNoUsers, scenarioSingleUser, scenarioSomeUsers };
	}

}}