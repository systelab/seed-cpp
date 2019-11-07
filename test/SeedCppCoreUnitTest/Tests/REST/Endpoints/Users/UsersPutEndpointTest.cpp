#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityPutEndpointTest.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"
#include "SeedCppCore/REST/Endpoints/Users/UsersPutEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONLoadTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockUserModelService.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct UsersPutEndpointWrapper
	{
		typedef model::User ModelEntity;
		typedef model::UserMgr ModelManager;
		typedef test_utility::MockUserModelService ModelEntityService;
		typedef rest::UsersPutEndpoint Endpoint;

		static void setUpSaveJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildUserSaveTranslatorProxy(_)).WillByDefault(Invoke(
				[](const ModelEntity& entityValue) -> dal::IJSONSaveTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONSaveTranslator>();
					ON_CALL(*jsonTranslator, saveEntityToJSON(_)).WillByDefault(Invoke(
						[entityValue](systelab::json::IJSONValue& jsonValue) -> void
						{
							jsonValue.addMember("id", *entityValue.getId());
							jsonValue.addMember("login", entityValue.getLogin());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static void setUpLoadJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildUserLoadTranslatorProxy(_)).WillByDefault(Invoke(
				[](ModelEntity& entityValue) -> dal::IJSONLoadTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONLoadTranslator>();
					ON_CALL(*jsonTranslator, loadEntityFromJSON(_)).WillByDefault(Invoke(
						[&entityValue](const systelab::json::IJSONValue& jsonValue) -> void
						{
							entityValue.setLogin(jsonValue.getObjectMemberValue("login").getString());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static std::vector<model::User> getEntities()
		{
			return { UserBuilder().setId("Id1"s).setLogin("username1").getEntity(),
					 UserBuilder().setId("Id2"s).setLogin("username2").getEntity(),
					 UserBuilder().setId("Id3"s).setLogin("username3").getEntity() };
		}

		static std::string getHappyPathNotFoundRequestIdParameter()
		{
			return "NotExistingUserId";
		}

		static std::string getHappyPathAlreadyExistingRequestIdParameter()
		{
			return "Id2";
		}

		static std::string getHappyPathRequestContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"login\": \"newusername\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static std::string getJSONSchema()
		{
			return "JSON_SCHEMA_ENDPOINT_USERS_PUT";
		}

		static ModelEntity getExpectedEntityToAddWhenNotFound()
		{
			model::User user;
			user.setLogin("newusername");
			return user;
		}

		static ModelEntity getExpectedEntityToEditWhenAlreadyExisting()
		{
			model::User user;
			user.setId("Id2"s);
			user.setLogin("newusername");
			return user;
		}

		static ModelEntity getAddedOrUpdatedEntity()
		{
			model::User user;
			user.setId("Id2"s);
			user.setLogin("newusername");
			return user;
		}

		static std::string getExpectedHappyPathReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"id\": \"Id2\"," << std::endl;
			ss << "    \"login\": \"newusername\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static void tearDownWrapper()
		{
		}
	};

	typedef ::testing::Types<
		UsersPutEndpointWrapper
	> UsersPutEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UsersPutEndpointTest, EntityPutEndpointTest, UsersPutEndpointWrappers);

}}