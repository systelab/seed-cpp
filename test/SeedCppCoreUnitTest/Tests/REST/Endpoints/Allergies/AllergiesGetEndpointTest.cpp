#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetEndpointTest.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"
#include "SeedCppCore/REST/Endpoints/Allergies/AllergiesGetEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/AllergyBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct AllergiesGetEndpointBaseWrapper
	{
		typedef model::Allergy ModelEntity;
		typedef model::AllergyMgr ModelManager;
		typedef rest::AllergiesGetEndpoint Endpoint;

		static void setUpJSONTranslatorsFactory(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildAllergySaveTranslatorProxy(_)).WillByDefault(Invoke(
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

	struct AllergiesGetEndpointEmptyMgrWrapper : public AllergiesGetEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			return {};
		}

		static std::string getIdentifierParameter()
		{
			return "AllergyToFind";
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

	struct AllergiesGetEndpointSingleEntityMgrWrapper : public AllergiesGetEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			return { AllergyBuilder().setId("SingleAllergyId").getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "SingleAllergyId";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"SingleAllergyId\" }";
		}
	};

	struct AllergiesGetEndpointMultipleEntitiesMgrWrapper : public AllergiesGetEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			return { AllergyBuilder().setId("Allergy1Id").getEntity(),
					 AllergyBuilder().setId("Allergy2Id").getEntity(),
					 AllergyBuilder().setId("Allergy3Id").getEntity(),
					 AllergyBuilder().setId("Allergy4Id").getEntity(),
					 AllergyBuilder().setId("Allergy5Id").getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "Allergy3Id";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Allergy3Id\" }";
		}
	};

	struct AllergiesGetEndpointFirstEntityOfMgrWrapper : public AllergiesGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "Allergy1Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Allergy1Id\" }";
		}
	};

	struct AllergiesGetEndpointLastEntityOfMgrWrapper : public AllergiesGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "Allergy5Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Allergy5Id\" }";
		}
	};

	struct AllergiesGetEndpointNotExistingEntityOfMgrWrapper : public AllergiesGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingAllergyId";
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
		AllergiesGetEndpointEmptyMgrWrapper,
		AllergiesGetEndpointSingleEntityMgrWrapper,
		AllergiesGetEndpointMultipleEntitiesMgrWrapper,
		AllergiesGetEndpointFirstEntityOfMgrWrapper,
		AllergiesGetEndpointLastEntityOfMgrWrapper,
		AllergiesGetEndpointNotExistingEntityOfMgrWrapper
	> AllergiesGetEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergiesGetEndpointTest, EntityGetEndpointTest, AllergiesGetEndpointWrappers);

}}