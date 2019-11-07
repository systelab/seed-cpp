#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"
#include "RapidJSONAdapter/JSONAdapter.h"
#include "WebServerAdapterInterface/Model/Reply.h"

#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONTranslatorsFactory.h"
#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace seed_cpp::test_utility;
using namespace systelab::json::test_utility;

namespace seed_cpp { namespace unit_test {

	template <typename _Wrapper>
	class EntityGetEndpointTest : public Test
	{
	public:
		EntityGetEndpointTest()
		{
		}

		void SetUp()
		{
			setUpEntityMgr();
			_Wrapper::setUpJSONTranslatorsFactory(m_jsonTranslatorsFactory);

			m_endpoint = std::make_unique<typename _Wrapper::Endpoint>(m_entityMgr, m_jsonTranslatorsFactory, m_jsonAdapter);
		}

		void TearDown()
		{
			_Wrapper::tearDownWrapper();
		}

		void setUpEntityMgr()
		{
			typename _Wrapper::ModelManager::UniqueLock writeLock(m_entityMgr);
			std::vector<typename _Wrapper::ModelEntity> entities = _Wrapper::getEntities();
			for (auto entity : entities)
			{
				m_entityMgr.addEntity(std::make_unique<typename _Wrapper::ModelEntity>(entity), writeLock);
			}
		}

	protected:
		std::unique_ptr<systelab::rest_api_core::IEndpoint> m_endpoint;
		test_utility::MockJSONTranslatorsFactory m_jsonTranslatorsFactory;
		typename _Wrapper::ModelManager m_entityMgr;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};

	TYPED_TEST_CASE_P(EntityGetEndpointTest);
	
	TYPED_TEST_P(EntityGetEndpointTest, testExecuteGetReturnsExpectedReply)
	{
		systelab::rest_api_core::EndpointRequestParams requestParams;
		requestParams.addStringParameter("id", TypeParam::getIdentifierParameter());

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setParameters(requestParams);
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(TypeParam::getExpectedReplyStatus(), reply->getStatus());

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));

		std::string expectedContent = TypeParam::getExpectedReplyContent();
		EXPECT_TRUE(compareJSONs(expectedContent, reply->getContent(), this->m_jsonAdapter));
	}

	REGISTER_TYPED_TEST_CASE_P(EntityGetEndpointTest, testExecuteGetReturnsExpectedReply);

}}

