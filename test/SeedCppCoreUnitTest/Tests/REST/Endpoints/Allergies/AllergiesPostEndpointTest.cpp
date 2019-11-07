#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityPostEndpointTest.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"
#include "SeedCppCore/REST/Endpoints/Allergies/AllergiesPostEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/AllergyBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONLoadTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockAllergyModelService.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct AllergiesPostEndpointWrapper
	{
		typedef model::Allergy ModelEntity;
		typedef model::AllergyMgr ModelManager;
		typedef test_utility::MockAllergyModelService ModelEntityService;
		typedef rest::AllergiesPostEndpoint Endpoint;

		static void setUpSaveJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildAllergySaveTranslatorProxy(_)).WillByDefault(Invoke(
				[](const ModelEntity& entityValue) -> dal::IJSONSaveTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONSaveTranslator>();
					ON_CALL(*jsonTranslator, saveEntityToJSON(_)).WillByDefault(Invoke(
						[entityValue](systelab::json::IJSONValue& jsonValue) -> void
						{
							jsonValue.addMember("id", *entityValue.getId());
							jsonValue.addMember("name", entityValue.getName());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static void setUpLoadJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildAllergyLoadTranslatorProxy(_)).WillByDefault(Invoke(
				[](ModelEntity& entityValue) -> dal::IJSONLoadTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONLoadTranslator>();
					ON_CALL(*jsonTranslator, loadEntityFromJSON(_)).WillByDefault(Invoke(
						[&entityValue](const systelab::json::IJSONValue& jsonValue) -> void
						{
							entityValue.setName(jsonValue.getObjectMemberValue("name").getString());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static std::string getHappyPathRequestContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"name\": \"Pollen\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static std::string getJSONSchema()
		{
			return "JSON_SCHEMA_ENDPOINT_ALLERGIES_POST";
		}

		static ModelEntity getExpectedEntityToAdd()
		{
			model::Allergy allergy;
			allergy.setName("Pollen");
			return allergy;
		}

		static ModelEntity getAddedEntity()
		{
			model::Allergy allergy;
			allergy.setId("EF410E08-2A25-4751-B1B5-CC03A28B4D2B"s);
			allergy.setName("Pollen");
			return allergy;
		}

		static std::string getExpectedHappyPathReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"id\": \"EF410E08-2A25-4751-B1B5-CC03A28B4D2B\"," << std::endl;
			ss << "    \"name\": \"Pollen\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static void tearDownWrapper()
		{
		}
	};

	typedef ::testing::Types<
		AllergiesPostEndpointWrapper
	> AllergiesPostEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergiesPostEndpointTest, EntityPostEndpointTest, AllergiesPostEndpointWrappers);

}}