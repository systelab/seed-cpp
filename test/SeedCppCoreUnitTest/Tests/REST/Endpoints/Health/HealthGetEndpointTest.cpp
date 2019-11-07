#include "stdafx.h"
#include "SeedCppCore/REST/Endpoints/Health/HealthGetEndpoint.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"
#include "WebServerAdapterInterface/Model/Reply.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace seed_cpp { namespace unit_test {

	class HealthGetEndpointTest : public Test
	{
		void SetUp()
		{
			m_endpoint = std::make_unique<rest::HealthGetEndpoint>();
		}

	protected:
		std::unique_ptr<rest::HealthGetEndpoint> m_endpoint;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};


	TEST_F(HealthGetEndpointTest, testExecuteReturnsReplyStatusOK)
	{
		auto reply = m_endpoint->execute(systelab::rest_api_core::EndpointRequestData());

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(systelab::web_server::Reply::OK, reply->getStatus());
	}

	TEST_F(HealthGetEndpointTest, testExecuteReturnsReplyContentWithEmptyJSON)
	{
		auto reply = m_endpoint->execute(systelab::rest_api_core::EndpointRequestData());

		ASSERT_TRUE(reply != nullptr);
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));
	}

	TEST_F(HealthGetEndpointTest, testExecuteReturnsReplyWithExpectedHeaders)
	{
		auto reply = m_endpoint->execute(systelab::rest_api_core::EndpointRequestData());

		ASSERT_TRUE(reply != nullptr);
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), m_jsonAdapter));

		ASSERT_TRUE(reply != nullptr);
		ASSERT_TRUE(reply->hasHeader("Content-Length"));
		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
	}

}}

