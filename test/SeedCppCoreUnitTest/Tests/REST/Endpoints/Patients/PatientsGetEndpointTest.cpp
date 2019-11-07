#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetEndpointTest.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/REST/Endpoints/Patients/PatientsGetEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct PatientsGetEndpointBaseWrapper
	{
		typedef model::Patient ModelEntity;
		typedef model::PatientMgr ModelManager;
		typedef rest::PatientsGetEndpoint Endpoint;

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

	struct PatientsGetEndpointEmptyMgrWrapper : public PatientsGetEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return {};
		}

		static std::string getIdentifierParameter()
		{
			return "PatientToFind";
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

	struct PatientsGetEndpointSingleEntityMgrWrapper : public PatientsGetEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return { PatientBuilder().setId("SinglePatientId").getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "SinglePatientId";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"SinglePatientId\" }";
		}
	};

	struct PatientsGetEndpointMultipleEntitiesMgrWrapper : public PatientsGetEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return { PatientBuilder().setId("Patient1Id").getEntity(),
					 PatientBuilder().setId("Patient2Id").getEntity(),
					 PatientBuilder().setId("Patient3Id").getEntity(),
					 PatientBuilder().setId("Patient4Id").getEntity(),
					 PatientBuilder().setId("Patient5Id").getEntity() };
		}

		static std::string getIdentifierParameter()
		{
			return "Patient3Id";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::OK;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Patient3Id\" }";
		}
	};

	struct PatientsGetEndpointFirstEntityOfMgrWrapper : public PatientsGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "Patient1Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Patient1Id\" }";
		}
	};

	struct PatientsGetEndpointLastEntityOfMgrWrapper : public PatientsGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "Patient5Id";
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"id\": \"Patient5Id\" }";
		}
	};

	struct PatientsGetEndpointNotExistingEntityOfMgrWrapper : public PatientsGetEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingPatientId";
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
		PatientsGetEndpointEmptyMgrWrapper,
		PatientsGetEndpointSingleEntityMgrWrapper,
		PatientsGetEndpointMultipleEntitiesMgrWrapper,
		PatientsGetEndpointFirstEntityOfMgrWrapper,
		PatientsGetEndpointLastEntityOfMgrWrapper,
		PatientsGetEndpointNotExistingEntityOfMgrWrapper
	> PatientsGetEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsGetEndpointTest, EntityGetEndpointTest, PatientsGetEndpointWrappers);

}}