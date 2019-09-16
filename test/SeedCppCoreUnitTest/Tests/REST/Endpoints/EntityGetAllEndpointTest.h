#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RapidJSONAdapter/JSONAdapter.h"

#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONTranslatorsFactory.h"
#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace seed_cpp::test_utility;
using namespace systelab::json::test_utility;

namespace seed_cpp { namespace unit_test {

	template <typename _Wrapper>
	class EntityGetAllEndpointTest : public Test
	{
	public:
		EntityGetAllEndpointTest()
		{
		}

		void SetUp()
		{
			setUpEntityMgr();
			_Wrapper::setUpJSONTranslatorsFactory(m_jsonTranslatorsFactory);

			m_endpoint = std::make_unique<_Wrapper::Endpoint>(m_entityMgr, m_jsonTranslatorsFactory, m_jsonAdapter);
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

	TYPED_TEST_CASE_P(EntityGetAllEndpointTest);
	
	TYPED_TEST_P(EntityGetAllEndpointTest, testExecuteGetAllReturnsStatusOKAndExpectedContent)
	{
		systelab::rest_api_core::EndpointRequestData requestData;
		std::unique_ptr<systelab::web_server::Reply> reply = m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(systelab::web_server::Reply::OK, reply->getStatus());

		std::string expectedContent = TypeParam::getExpectedReplyContent();
		EXPECT_TRUE(compareJSONs(expectedContent, reply->getContent(), m_jsonAdapter));
	}

	REGISTER_TYPED_TEST_CASE_P(EntityGetAllEndpointTest, testExecuteGetAllReturnsStatusOKAndExpectedContent);

}}

