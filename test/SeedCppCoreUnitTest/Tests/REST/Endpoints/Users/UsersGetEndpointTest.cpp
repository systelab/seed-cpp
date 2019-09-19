#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetEndpointTest.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"
#include "SeedCppCore/REST/Endpoints/Users/UsersGetEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct UsersGetEndpointBaseWrapper
	{
		typedef model::User ModelEntity;
		typedef model::UserMgr ModelManager;
		typedef rest::UsersGetEndpoint Endpoint;

		static void setUpJSONTranslatorsFactory(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildUserSaveTranslatorProxy(_)).WillByDefault(Invoke(
				[](const ModelEntity& entityValue) -> dal::IJSONSaveTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONSaveTranslator>();
					EXPECT_CALL(*jsonTranslator, saveEntityToJSON(_)).WillOnce(Invoke(
						[entityValue](systelab::json::IJSONValue& jsonValue) -> void
						{
							jsonValue.addMember("id", *entityValue.getId());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static void tearDownWrapper()
		{
		}
	};

	struct UsersGetEndpointEmptyMgrWrapper : public UsersGetEndpointBaseWrapper
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

		static std::string getExpectedReplyContent()
		{
			return "{}";
		}
	};

	struct UsersGetEndpointSingleEntityMgrWrapper : public UsersGetEndpointBaseWrapper
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
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"SingleUserId\" }";
		}
	};

	struct UsersGetEndpointMultipleEntitiesMgrWrapper : public UsersGetEndpointBaseWrapper
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
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"User3Id\" }";
		}
	};

	struct UsersGetEndpointFirstEntityOfMgrWrapper : public UsersGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "User1Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"User1Id\" }";
		}
	};

	struct UsersGetEndpointLastEntityOfMgrWrapper : public UsersGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "User5Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"User5Id\" }";
		}
	};

	struct UsersGetEndpointNotExistingEntityOfMgrWrapper : public UsersGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingUserId";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NOT_FOUND;
		}

		static std::string getExpectedReplyContent()
		{
			return "{}";
		}
	};


	typedef ::testing::Types<
		UsersGetEndpointEmptyMgrWrapper,
		UsersGetEndpointSingleEntityMgrWrapper,
		UsersGetEndpointMultipleEntitiesMgrWrapper,
		UsersGetEndpointFirstEntityOfMgrWrapper,
		UsersGetEndpointLastEntityOfMgrWrapper,
		UsersGetEndpointNotExistingEntityOfMgrWrapper
	> UsersGetEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UsersGetEndpointTest, EntityGetEndpointTest, UsersGetEndpointWrappers);

}}