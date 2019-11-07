#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityPutEndpointTest.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/REST/Endpoints/Patients/PatientsPutEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONLoadTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockPatientModelService.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct PatientsPutEndpointWrapper
	{
		typedef model::Patient ModelEntity;
		typedef model::PatientMgr ModelManager;
		typedef test_utility::MockPatientModelService ModelEntityService;
		typedef rest::PatientsPutEndpoint Endpoint;

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

		static std::vector<model::Patient> getEntities()
		{
			return { PatientBuilder().setId("Id1"s).setEmail("Patient1@werfen.com").getEntity(),
					 PatientBuilder().setId("Id2"s).setEmail("Patient2@werfen.com").getEntity(),
					 PatientBuilder().setId("Id3"s).setEmail("Patient3@werfen.com").getEntity() };
		}

		static std::string getHappyPathNotFoundRequestIdParameter()
		{
			return "NotExistingPatientId";
		}

		static std::string getHappyPathAlreadyExistingRequestIdParameter()
		{
			return "Id2";
		}

		static std::string getHappyPathRequestContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"email\": \"updated@werfen.com\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static std::string getJSONSchema()
		{
			return "JSON_SCHEMA_ENDPOINT_PATIENTS_PUT";
		}

		static ModelEntity getExpectedEntityToAddWhenNotFound()
		{
			model::Patient patient;
			patient.setEmail("updated@werfen.com");
			return patient;
		}

		static ModelEntity getExpectedEntityToEditWhenAlreadyExisting()
		{
			model::Patient patient;
			patient.setId("Id2"s);
			patient.setEmail("updated@werfen.com");
			return patient;
		}

		static ModelEntity getAddedOrUpdatedEntity()
		{
			model::Patient patient;
			patient.setId("Id2"s);
			patient.setEmail("updated@werfen.com");
			return patient;
		}

		static std::string getExpectedHappyPathReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"id\": \"Id2\"," << std::endl;
			ss << "    \"email\": \"updated@werfen.com\" " << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		static void tearDownWrapper()
		{
		}
	};

	typedef ::testing::Types<
		PatientsPutEndpointWrapper
	> PatientsPutEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsPutEndpointTest, EntityPutEndpointTest, PatientsPutEndpointWrappers);

}}