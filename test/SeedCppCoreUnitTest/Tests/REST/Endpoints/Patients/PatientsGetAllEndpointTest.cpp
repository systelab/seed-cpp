#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetAllEndpointTest.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/REST/Endpoints/Patients/PatientsGetAllEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct PatientsGetAllEndpointBaseWrapper
	{
		typedef model::Patient ModelEntity;
		typedef model::PatientMgr ModelManager;
		typedef rest::PatientsGetAllEndpoint Endpoint;

		static void setUpJSONTranslatorsFactory(MockJSONTranslatorsFactory& jsonTranslatorsFactory)
		{
			ON_CALL(jsonTranslatorsFactory, buildPatientSaveTranslatorProxy(_)).WillByDefault(Invoke(
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

	struct PatientsGetAllEndpointEmptyWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return {};
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": []," << std::endl;
			ss << "   \"totalElements\": 0," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 0," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 0" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct PatientsGetAllEndpointSingleEntityWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return { PatientBuilder().setId("Patient1").getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient1\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 1," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 1," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 1" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};



	typedef ::testing::Types<
		PatientsGetAllEndpointEmptyWrapper,
		PatientsGetAllEndpointSingleEntityWrapper
	> PatientsGetAllEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsGetAllEndpointTest, EntityGetAllEndpointTest, PatientsGetAllEndpointWrappers);

}}