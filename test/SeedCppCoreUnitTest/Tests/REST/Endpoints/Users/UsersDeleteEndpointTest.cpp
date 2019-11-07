#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityDeleteEndpointTest.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"
#include "SeedCppCore/REST/Endpoints/Users/UsersDeleteEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockUserModelService.h"


using namespace testing;
using namespace std::string_literals;
using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace unit_test {

	struct UsersDeleteEndpointBaseWrapper
	{
		typedef model::User ModelEntity;
		typedef model::UserMgr ModelManager;
		typedef test_utility::MockUserModelService ModelEntityService;
		typedef rest::UsersDeleteEndpoint Endpoint;

		static bool getExceptionOnDeletion()
		{
			return false;
		}

		static std::string getExpectedReplyContent()
		{
			return "{}";
		}

		static void tearDownWrapper()
		{
		}
	};

	struct UsersDeleteEndpointEmptyMgrWrapper : public UsersDeleteEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return {};
		}

		static std::string getIdentifierParameter()
		{
			return "UserToFind";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NOT_FOUND;
		}

		static bool getExpectedEntityDeletion()
		{
			return false;
		}
	};

	struct UsersDeleteEndpointSingleEntityMgrWrapper : public UsersDeleteEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return { UserBuilder().setId("SingleUserId"s).getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "SingleUserId";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct UserDeleteEndpointMultipleEntitiesMgrWrapper : public UsersDeleteEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return { UserBuilder().setId("User1Id"s).getEntity(),
					 UserBuilder().setId("User2Id"s).getEntity(),
					 UserBuilder().setId("User3Id"s).getEntity(),
					 UserBuilder().setId("User4Id"s).getEntity(),
					 UserBuilder().setId("User5Id"s).getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "User3Id";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct UsersDeleteEndpointNotExistingEntityWrapper : public UserDeleteEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingUser";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NOT_FOUND;
		}

		static bool getExpectedEntityDeletion()
		{
			return false;
		}
	};

	struct UsersDeleteEndpointExceptionOnDeletionWrapper : public UserDeleteEndpointMultipleEntitiesMgrWrapper
	{
		static bool getExceptionOnDeletion()
		{
			return true;
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::INTERNAL_SERVER_ERROR;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"exception\": \"Internal error\" }";
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};


	typedef ::testing::Types<
		UsersDeleteEndpointEmptyMgrWrapper,
		UsersDeleteEndpointSingleEntityMgrWrapper,
		UserDeleteEndpointMultipleEntitiesMgrWrapper,
		UsersDeleteEndpointNotExistingEntityWrapper,
		UsersDeleteEndpointExceptionOnDeletionWrapper
	> UsersDeleteEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UsersDeleteEndpointTest, EntityDeleteEndpointTest, UsersDeleteEndpointWrappers);

}}