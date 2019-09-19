#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"
#include "RapidJSONAdapter/JSONAdapter.h"
#include "WebServerAdapterInterface/Model/Reply.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace seed_cpp { namespace unit_test {

	template <typename _Wrapper>
	class EntityDeleteEndpointTest : public Test
	{
	public:
		EntityDeleteEndpointTest()
		{
		}

		void SetUp()
		{
			setUpEntityMgr();
			setUpEntityModelService();

			m_endpoint = std::make_unique<typename _Wrapper::Endpoint>(m_entityModelService);
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

		void setUpEntityModelService()
		{
			ON_CALL(m_entityModelService, createWriteLockProxy()).WillByDefault(Invoke(
				[this]() -> model::LockableEntityMgrSubject::IWriteLock*
				{
					return new typename _Wrapper::ModelManager::UniqueLock(m_entityMgr);
				}
			));

			ON_CALL(m_entityModelService, getEntityById(_, _)).WillByDefault(Invoke(
				[this](const std::string& id, const model::LockableEntityMgrSubject::IReadLock& readLock) -> const typename _Wrapper::ModelEntity*
				{
					return m_entityMgr.getEntityById(id, readLock);
				}
			));
		}

	protected:
		std::unique_ptr<systelab::rest_api_core::IEndpoint> m_endpoint;
		typename _Wrapper::ModelManager m_entityMgr;
		typename _Wrapper::ModelEntityService m_entityModelService;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};

	TYPED_TEST_CASE_P(EntityDeleteEndpointTest);
	
	TYPED_TEST_P(EntityDeleteEndpointTest, testExecute)
	{
		std::string workingEntityId = TypeParam::getIdentifierParameter();
		EXPECT_CALL(m_entityModelService, deleteEntity(workingEntityId, _)).Times(TypeParam::getExpectedEntityDeletion() ? 1 : 0);

		systelab::rest_api_core::EndpointRequestParams requestParams;
		requestParams.addStringParameter("id", workingEntityId);

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setParameters(requestParams);
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(TypeParam::getExpectedReplyStatus(), reply->getStatus());

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));

		std::string expectedContent = "{}";
		EXPECT_TRUE(compareJSONs(expectedContent, reply->getContent(), this->m_jsonAdapter));
	}

	REGISTER_TYPED_TEST_CASE_P(EntityDeleteEndpointTest, testExecute);

}}

