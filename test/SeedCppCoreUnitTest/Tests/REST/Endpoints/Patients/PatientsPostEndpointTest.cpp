#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityPostEndpointTest.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/REST/Endpoints/Patients/PatientsPostEndpoint.h"

#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONLoadTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockPatientModelService.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct PatientsPostEndpointWrapper
	{
		typedef model::Patient ModelEntity;
		typedef model::PatientMgr ModelManager;
		typedef test_utility::MockPatientModelService ModelEntityService;
		typedef rest::PatientsPostEndpoint Endpoint;

		static void setUpSaveJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildPatientSaveTranslatorProxy(_)).WillByDefault(Invoke(
				[](const ModelEntity& entityValue) -> dal::IJSONSaveTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONSaveTranslator>();
					ON_CALL(*jsonTranslator, saveEntityToJSON(_)).WillByDefault(Invoke(
						[entityValue](systelab::json::IJSONValue& jsonValue) -> void
						{
							jsonValue.addMember("id", *entityValue.getId());
							jsonValue.addMember("email", entityValue.getEmail());
						}
					));

					return jsonTranslator.release();
				}
			));
		}

		static void setUpLoadJSONTranslator(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildPatientLoadTranslatorProxy(_)).WillByDefault(Invoke(
				[](ModelEntity& entityValue) -> dal::IJSONLoadTranslator*
				{
					auto jsonTranslator = std::make_unique<MockJSONLoadTranslator>();
					ON_CALL(*jsonTranslator, loadEntityFromJSON(_)).WillByDefault(Invoke(
						[&entityValue](const systelab::json::IJSONValue& jsonValue) -> void
						{
							entityValue.setEmail(jsonValue.getObjectMemberValue("email").getString());
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
			ss << "    \"email\": \"peter.parker@werfen.com\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static std::string getJSONSchema()
		{
			return "JSON_SCHEMA_ENDPOINT_PATIENTS_POST";
		}

		static ModelEntity getExpectedEntityToAdd()
		{
			model::Patient patient;
			patient.setEmail("peter.parker@werfen.com");
			return patient;
		}

		static ModelEntity getAddedEntity()
		{
			model::Patient patient;
			patient.setId("CB8800CF-B200-42A1-93E7-D7B679D4CF34"s);
			patient.setEmail("peter.parker@werfen.com");
			return patient;
		}

		static std::string getExpectedHappyPathReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"id\": \"CB8800CF-B200-42A1-93E7-D7B679D4CF34\"," << std::endl;
			ss << "    \"email\": \"peter.parker@werfen.com\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static void tearDownWrapper()
		{
		}
	};

	typedef ::testing::Types<
		PatientsPostEndpointWrapper
	> PatientsPostEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsPostEndpointTest, EntityPostEndpointTest, PatientsPostEndpointWrappers);

}}