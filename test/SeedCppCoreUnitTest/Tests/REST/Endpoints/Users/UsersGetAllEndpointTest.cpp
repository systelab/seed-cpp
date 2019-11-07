#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetAllEndpointTest.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"
#include "SeedCppCore/REST/Endpoints/Users/UsersGetAllEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/UserBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct UsersGetAllEndpointBaseWrapper
	{
		typedef model::User ModelEntity;
		typedef model::UserMgr ModelManager;
		typedef rest::UsersGetAllEndpoint Endpoint;

		static std::map<std::string, std::string> getQueryStrings()
		{
			return {};
		}

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

	struct UsersGetAllEndpointEmptyWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return {};
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": []," << std::endl;
			ss << "   \"totalElements\": 0," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 0," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 0" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointSingleEntityWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return { UserBuilder().setId("User1"s).getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User1\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 1," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 1," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 1" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointSinglePageWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			return { UserBuilder().setId("User1"s).getEntity(),
					 UserBuilder().setId("User2"s).getEntity(),
					 UserBuilder().setId("User3"s).getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User1\" }," << std::endl;
			ss << "      { \"id\": \"User2\" }," << std::endl;
			ss << "      { \"id\": \"User3\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 3," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 3," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 1" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointFirstPageWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::vector<model::User> getEntities()
		{
			std::vector<model::User> users;
			for (unsigned int i = 1; i <= 96; i++)
			{
				users.push_back(UserBuilder().setId("User" + std::to_string(i)).getEntity());
			}

			return users;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User1\"  }," << std::endl;
			ss << "      { \"id\": \"User2\"  }," << std::endl;
			ss << "      { \"id\": \"User3\"  }," << std::endl;
			ss << "      { \"id\": \"User4\"  }," << std::endl;
			ss << "      { \"id\": \"User5\"  }," << std::endl;
			ss << "      { \"id\": \"User6\"  }," << std::endl;
			ss << "      { \"id\": \"User7\"  }," << std::endl;
			ss << "      { \"id\": \"User8\"  }," << std::endl;
			ss << "      { \"id\": \"User9\"  }," << std::endl;
			ss << "      { \"id\": \"User10\" }," << std::endl;
			ss << "      { \"id\": \"User11\" }," << std::endl;
			ss << "      { \"id\": \"User12\" }," << std::endl;
			ss << "      { \"id\": \"User13\" }," << std::endl;
			ss << "      { \"id\": \"User14\" }," << std::endl;
			ss << "      { \"id\": \"User15\" }," << std::endl;
			ss << "      { \"id\": \"User16\" }," << std::endl;
			ss << "      { \"id\": \"User17\" }," << std::endl;
			ss << "      { \"id\": \"User18\" }," << std::endl;
			ss << "      { \"id\": \"User19\" }," << std::endl;
			ss << "      { \"id\": \"User20\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 96," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 20," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 5" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointMidPageWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "1"} };
		}

		static std::vector<model::User> getEntities()
		{
			std::vector<model::User> users;
			for (unsigned int i = 1; i <= 67; i++)
			{
				users.push_back(UserBuilder().setId("User" + std::to_string(i)).getEntity());
			}

			return users;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User21\" }," << std::endl;
			ss << "      { \"id\": \"User22\" }," << std::endl;
			ss << "      { \"id\": \"User23\" }," << std::endl;
			ss << "      { \"id\": \"User24\" }," << std::endl;
			ss << "      { \"id\": \"User25\" }," << std::endl;
			ss << "      { \"id\": \"User26\" }," << std::endl;
			ss << "      { \"id\": \"User27\" }," << std::endl;
			ss << "      { \"id\": \"User28\" }," << std::endl;
			ss << "      { \"id\": \"User29\" }," << std::endl;
			ss << "      { \"id\": \"User30\" }," << std::endl;
			ss << "      { \"id\": \"User31\" }," << std::endl;
			ss << "      { \"id\": \"User32\" }," << std::endl;
			ss << "      { \"id\": \"User33\" }," << std::endl;
			ss << "      { \"id\": \"User34\" }," << std::endl;
			ss << "      { \"id\": \"User35\" }," << std::endl;
			ss << "      { \"id\": \"User36\" }," << std::endl;
			ss << "      { \"id\": \"User37\" }," << std::endl;
			ss << "      { \"id\": \"User38\" }," << std::endl;
			ss << "      { \"id\": \"User39\" }," << std::endl;
			ss << "      { \"id\": \"User40\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 67," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 1," << std::endl;
			ss << "   \"numberOfElements\": 20," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 4" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointLastPageWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "3"} };
		}

		static std::vector<model::User> getEntities()
		{
			std::vector<model::User> users;
			for (unsigned int i = 1; i <= 67; i++)
			{
				users.push_back(UserBuilder().setId("User" + std::to_string(i)).getEntity());
			}

			return users;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User61\" }," << std::endl;
			ss << "      { \"id\": \"User62\" }," << std::endl;
			ss << "      { \"id\": \"User63\" }," << std::endl;
			ss << "      { \"id\": \"User64\" }," << std::endl;
			ss << "      { \"id\": \"User65\" }," << std::endl;
			ss << "      { \"id\": \"User66\" }," << std::endl;
			ss << "      { \"id\": \"User67\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 67," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 3," << std::endl;
			ss << "   \"numberOfElements\": 7," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 4" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointCustomPageSizeWrapper : public UsersGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "2"}, {"size", "5"} };
		}

		static std::vector<model::User> getEntities()
		{
			std::vector<model::User> users;
			for (unsigned int i = 1; i <= 100; i++)
			{
				users.push_back(UserBuilder().setId("User" + std::to_string(i)).getEntity());
			}

			return users;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"User11\" }," << std::endl;
			ss << "      { \"id\": \"User12\" }," << std::endl;
			ss << "      { \"id\": \"User13\" }," << std::endl;
			ss << "      { \"id\": \"User14\" }," << std::endl;
			ss << "      { \"id\": \"User15\" }"  << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 100," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 2," << std::endl;
			ss << "   \"numberOfElements\": 5," << std::endl;
			ss << "   \"size\": 5," << std::endl;
			ss << "   \"totalPages\": 20" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct UsersGetAllEndpointInvalidPageQueryStringWrapper : public UsersGetAllEndpointFirstPageWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "invalid"} };
		}
	};

	struct UsersGetAllEndpointInvalidSizeQueryStringWrapper : public UsersGetAllEndpointFirstPageWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"size", "invalid"} };
		}
	};


	typedef ::testing::Types<
		UsersGetAllEndpointEmptyWrapper,
		UsersGetAllEndpointSingleEntityWrapper,
		UsersGetAllEndpointSinglePageWrapper,
		UsersGetAllEndpointFirstPageWrapper,
		UsersGetAllEndpointMidPageWrapper,
		UsersGetAllEndpointLastPageWrapper,
		UsersGetAllEndpointCustomPageSizeWrapper,
		UsersGetAllEndpointInvalidPageQueryStringWrapper,
		UsersGetAllEndpointInvalidSizeQueryStringWrapper
	> UsersGetAllEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UsersGetAllEndpointTest, EntityGetAllEndpointTest, UsersGetAllEndpointWrappers);

}}