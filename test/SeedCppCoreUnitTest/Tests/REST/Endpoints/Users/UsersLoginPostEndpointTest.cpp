#include "stdafx.h"
#include "SeedCppCore/REST/Endpoints/Users/UsersLoginPostEndpoint.h"

#include "SeedCppCore/Model/Settings.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"
#include "WebServerAdapterInterface/Model/Reply.h"

#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockUserModelService.h"
#include "SeedCppCoreTestUtilities/Stubs/Services/System/StubTimeService.h"
#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"
#include "JSONSettingsTestUtilities/Mocks/MockSettingsService.h"
#include "JWTUtilsTestUtilities/Mocks/MockTokenBuilderService.h"


using namespace testing;
using namespace seed_cpp::test_utility;
using namespace systelab::json::test_utility;
using namespace systelab::jwt::test_utility;
using namespace systelab::setting::test_utility;

namespace seed_cpp { namespace unit_test {

	class UsersLoginPostEndpointTest : public Test
	{
	public:
		void SetUp()
		{
			setUpUserModelService();
			setUpTimeService();
			setUpTokenBuilderService();
			setUpSettingsService();

			m_endpoint = std::make_unique<rest::UsersLoginPostEndpoint>
							(m_userModelService, m_timeService, m_tokenBuilderService, m_settingsService);
		}

		void setUpUserModelService()
		{
			m_existingUser = std::make_unique<model::User>();
			m_existingUser->setLogin("jsmith");
			m_existingUser->setPassword("iamtheboss");

			ON_CALL(m_userModelService, getUserByLogin(_, _)).WillByDefault(ReturnNull());
			ON_CALL(m_userModelService, getUserByLogin(Eq(m_existingUser->getLogin()), _)).WillByDefault(Return(m_existingUser.get()));

			ON_CALL(m_userModelService, getEntityMgr()).WillByDefault(ReturnRef(m_userMgr));
		}

		void setUpTimeService()
		{
			m_currentTime = boost::posix_time::from_iso_string("20201126T095437");
			m_timeService.setCurrentTime(m_currentTime);
		}

		void setUpTokenBuilderService()
		{
			m_generatedToken = "GeneratedToken";
			ON_CALL(m_tokenBuilderService, buildJWT(_, _)).WillByDefault(Return(m_generatedToken));
		}

		void setUpSettingsService()
		{
			m_jwtSecretKey = "MySecretKey";
			ON_CALL_JSON_SETTING_STR(m_settingsService, model::setting::ApplicationSettingsFile, JWTSecretKey, m_jwtSecretKey)
		}

		systelab::rest_api_core::EndpointRequestData buildHappyPathEndpointRequestData()
		{
			return buildCredentialsEndpointRequestData(m_existingUser->getLogin(), m_existingUser->getPassword());
		}

		systelab::rest_api_core::EndpointRequestData buildCredentialsEndpointRequestData(const std::string& login, const std::string& password)
		{
			std::stringstream ss;
			ss << "login=" << login << "&password=" << password;
			std::string content = ss.str();

			return buildEndpointRequestData(content);
		}

		systelab::rest_api_core::EndpointRequestData buildEndpointRequestData(const std::string& content)
		{
			systelab::rest_api_core::EndpointRequestData requestData;
			requestData.setContent(content);
			return requestData;
		}

	protected:
		std::unique_ptr<rest::UsersLoginPostEndpoint> m_endpoint;
		MockUserModelService m_userModelService;
		StubTimeService m_timeService;
		MockTokenBuilderService m_tokenBuilderService;
		MockSettingsService m_settingsService;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;

		model::UserMgr m_userMgr;
		std::unique_ptr<model::User> m_existingUser;
		boost::posix_time::ptime m_currentTime;
		std::string m_jwtSecretKey;
		std::string m_generatedToken;
	};


	// Happy path
	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathReturnsReplyStatusOK)
	{
		auto reply = m_endpoint->execute(buildHappyPathEndpointRequestData());
		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::OK, reply->getStatus());
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathReturnsReplyContentWithEmptyJSON)
	{
		auto reply = m_endpoint->execute(buildHappyPathEndpointRequestData());
		ASSERT_TRUE(reply != nullptr);
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathReturnsReplyWithExpectedHeaders)
	{
		auto reply = m_endpoint->execute(buildHappyPathEndpointRequestData());

		ASSERT_TRUE(reply != nullptr);
		ASSERT_TRUE(reply->hasHeader("Authorization"));
		ASSERT_TRUE(reply->hasHeader("Content-Length"));
		ASSERT_TRUE(reply->hasHeader("Content-Type"));

		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
		EXPECT_EQ("Bearer " + m_generatedToken, reply->getHeader("Authorization"));
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathBuildsJWTUsingSecretKey)
	{
		EXPECT_CALL(m_tokenBuilderService, buildJWT(Eq(m_jwtSecretKey), _));
		m_endpoint->execute(buildHappyPathEndpointRequestData());
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathBuildsJWTWithIATClaimOfCurrentTime)
	{
		std::string epochTimeStr = std::to_string(boost::posix_time::to_time_t(m_currentTime));
		std::pair<std::string, std::string> expectedClaim = { "iat", epochTimeStr };
		EXPECT_CALL(m_tokenBuilderService, buildJWT(_, Contains(expectedClaim)));

		m_endpoint->execute(buildHappyPathEndpointRequestData());
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForHappyPathBuildsJWTWithSUBClaimOfUserLogin)
	{
		std::pair<std::string, std::string> expectedClaim = { "sub", m_existingUser->getLogin() };
		EXPECT_CALL(m_tokenBuilderService, buildJWT(_, Contains(expectedClaim)));

		m_endpoint->execute(buildHappyPathEndpointRequestData());
	}


	// Unauthorized requests
	TEST_F(UsersLoginPostEndpointTest, testExecuteForNotExistingUserReturnsReplyStatusUnauthorized)
	{
		auto reply = m_endpoint->execute(buildCredentialsEndpointRequestData("invalidUser", m_existingUser->getPassword()));

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::UNAUTHORIZED, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
		EXPECT_FALSE(reply->hasHeader("Authorization"));
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForInvalidPasswordReturnsReplyStatusUnauthorized)
	{
		auto reply = m_endpoint->execute(buildCredentialsEndpointRequestData(m_existingUser->getLogin(), "invalidPassword"));

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::UNAUTHORIZED, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
		EXPECT_FALSE(reply->hasHeader("Authorization"));
	}


	// Bad requests
	TEST_F(UsersLoginPostEndpointTest, testExecuteForNotAnURLEncodedRequestContentReturnsReplyStatusBadRequest)
	{
		auto reply = m_endpoint->execute(buildEndpointRequestData("NotAnURLEncodedContent"));

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::BAD_REQUEST, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
		EXPECT_FALSE(reply->hasHeader("Authorization"));
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForRequestContentWithoutLoginReturnsReplyStatusBadRequest)
	{
		auto reply = m_endpoint->execute(buildEndpointRequestData("password=" + m_existingUser->getPassword()));

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::BAD_REQUEST, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
		EXPECT_FALSE(reply->hasHeader("Authorization"));
	}

	TEST_F(UsersLoginPostEndpointTest, testExecuteForRequestContentWithoutPasswordReturnsReplyStatusBadRequest)
	{
		auto reply = m_endpoint->execute(buildEndpointRequestData("login=" + m_existingUser->getLogin()));

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::BAD_REQUEST, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
		EXPECT_FALSE(reply->hasHeader("Authorization"));
	}

}}

