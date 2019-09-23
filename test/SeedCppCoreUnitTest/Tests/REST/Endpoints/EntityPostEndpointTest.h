#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "SeedCppCore/Model/LockableEntityMgrSubject.h"
#include "RapidJSONAdapter/JSONAdapter.h"
#include "WebServerAdapterInterface/Model/Reply.h"

#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONTranslatorsFactory.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Validator/MockJSONValidatorService.h"
#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"
#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::test_utility;
using namespace systelab::test_utility;
using namespace systelab::json::test_utility;

namespace seed_cpp { namespace unit_test {

	template <typename _Wrapper>
	class EntityPostEndpointTest : public Test
	{
	public:
		EntityPostEndpointTest()
		{
		}

		void SetUp()
		{
			setUpEntityModelService();
			setUpJSONTranslatorsFactory();

			m_endpoint = std::make_unique<typename _Wrapper::Endpoint>
							(m_jsonTranslatorsFactory, m_entityModelService,
							 m_jsonValidatorService, m_jsonAdapter);
		}

		void TearDown()
		{
			_Wrapper::tearDownWrapper();
		}

		void setUpJSONTranslatorsFactory()
		{
			_Wrapper::setUpLoadJSONTranslator(m_jsonTranslatorsFactory);
			_Wrapper::setUpSaveJSONTranslator(m_jsonTranslatorsFactory);
		}

		void setUpEntityModelService()
		{
			ON_CALL(m_entityModelService, createWriteLockProxy()).WillByDefault(Invoke(
				[this]() -> model::LockableEntityMgrSubject::IWriteLock*
				{
					return new typename _Wrapper::ModelManager::UniqueLock(m_entityMgr);
				}
			));

			m_addedEntity = _Wrapper::getAddedEntity();
			ON_CALL(m_entityModelService, addEntityProxy(_, _)).WillByDefault(Invoke(
				[this](typename _Wrapper::ModelEntity* entity,
					   const model::LockableEntityMgrSubject::IWriteLock&) -> const typename _Wrapper::ModelEntity&
				{
					return m_addedEntity;
				}
			));
		}

	protected:
		std::unique_ptr<systelab::rest_api_core::IEndpoint> m_endpoint;
		test_utility::MockJSONTranslatorsFactory m_jsonTranslatorsFactory;
		typename _Wrapper::ModelManager m_entityMgr;
		typename _Wrapper::ModelEntityService m_entityModelService;
		typename _Wrapper::ModelEntity m_addedEntity;
		MockJSONValidatorService m_jsonValidatorService;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};

	TYPED_TEST_CASE_P(EntityPostEndpointTest);
	

	// Happy path
	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForHappyPathReturnsCreatedStatus)
	{
		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent(TypeParam::getHappyPathRequestContent());
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(systelab::web_server::Reply::CREATED, reply->getStatus());
	}

	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForHappyPathReturnsExpectedReplyContent)
	{
		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent(TypeParam::getHappyPathRequestContent());
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);
		ASSERT_TRUE(reply != NULL);

		std::string expectedContent = TypeParam::getExpectedHappyPathReplyContent();
		EXPECT_TRUE(compareJSONs(expectedContent, reply->getContent(), this->m_jsonAdapter));

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
	}

	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForHappyPathValidatesRequestContentUsingExpectedJSONSchema)
	{
		std::string jsonSchema = TypeParam::getJSONSchema();
		EXPECT_CALL(m_jsonValidatorService, validate(_, Eq(jsonSchema)));

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent(TypeParam::getHappyPathRequestContent());
		this->m_endpoint->execute(requestData);
	}

	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForHappyPathAddsGivenEntityThroughModelService)
	{
		auto expectedEntityToAdd = TypeParam::getExpectedEntityToAdd();
		EXPECT_CALL(this->m_entityModelService, addEntityProxy(Pointee(isEqualTo(expectedEntityToAdd)), _));

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent(TypeParam::getHappyPathRequestContent());
		this->m_endpoint->execute(requestData);
	}


	// Error cases
	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForNotJSONRequestContentReturnsBadRequestStatus)
	{
		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent("This is not a JSON");
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(systelab::web_server::Reply::BAD_REQUEST, reply->getStatus());
		EXPECT_TRUE(compareJSONs("{}", reply->getContent(), this->m_jsonAdapter));

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
	}

	TYPED_TEST_P(EntityPostEndpointTest, testExecuteForJSONThatDoesNotStatisfySchemaReturnsBadRequestStatus)
	{
		std::string exceptionMessage = "JSON schema failure";
		ON_CALL(this->m_jsonValidatorService, validate(_, _))
			.WillByDefault(Throw(service::IJSONValidatorService::JSONValidationException(exceptionMessage)));

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent("{ \"value\": \"JSON that does not satisfy schema\" }");
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(systelab::web_server::Reply::BAD_REQUEST, reply->getStatus());

		std::string expectedJSON = "{ \"reason\": \"" + exceptionMessage + "\"}";
		EXPECT_TRUE(compareJSONs(expectedJSON, reply->getContent(), this->m_jsonAdapter));

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
	}

	TYPED_TEST_P(EntityPostEndpointTest, testExecuteThatThrowsExceptionWhileAddingEntityReturnsInternalServerErrorStatus)
	{
		std::string exceptionMessage = "Internal error while adding entity";
		ON_CALL(m_entityModelService, addEntityProxy(_, _))
			.WillByDefault(Throw(std::runtime_error(exceptionMessage)));

		systelab::rest_api_core::EndpointRequestData requestData;
		requestData.setContent(TypeParam::getHappyPathRequestContent());
		std::unique_ptr<systelab::web_server::Reply> reply = this->m_endpoint->execute(requestData);

		ASSERT_TRUE(reply != NULL);
		EXPECT_EQ(systelab::web_server::Reply::INTERNAL_SERVER_ERROR , reply->getStatus());

		std::string expectedJSON = "{ \"exception\": \"" + exceptionMessage + "\"}";
		EXPECT_TRUE(compareJSONs(expectedJSON, reply->getContent(), this->m_jsonAdapter));

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));
	}

	REGISTER_TYPED_TEST_CASE_P(EntityPostEndpointTest,
							   testExecuteForHappyPathReturnsCreatedStatus,
							   testExecuteForHappyPathReturnsExpectedReplyContent,
							   testExecuteForHappyPathValidatesRequestContentUsingExpectedJSONSchema,
							   testExecuteForHappyPathAddsGivenEntityThroughModelService,
							   testExecuteForNotJSONRequestContentReturnsBadRequestStatus,
							   testExecuteForJSONThatDoesNotStatisfySchemaReturnsBadRequestStatus,
							   testExecuteThatThrowsExceptionWhileAddingEntityReturnsInternalServerErrorStatus);

}}

