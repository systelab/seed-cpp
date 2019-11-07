#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityDeleteEndpointTest.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/REST/Endpoints/Patients/PatientsDeleteEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockPatientModelService.h"


using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct PatientsDeleteEndpointBaseWrapper
	{
		typedef model::Patient ModelEntity;
		typedef model::PatientMgr ModelManager;
		typedef test_utility::MockPatientModelService ModelEntityService;
		typedef rest::PatientsDeleteEndpoint Endpoint;

		static bool getExceptionOnDeletion()
		{
			return false;
		}

		static std::string getExpectedReplyContent()
		{
			return "{}";
		}

		static void tearDownWrapper()
		{
		}
	};

	struct PatientsDeleteEndpointEmptyMgrWrapper : public PatientsDeleteEndpointBaseWrapper
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

		static bool getExpectedEntityDeletion()
		{
			return false;
		}
	};

	struct PatientsDeleteEndpointSingleEntityMgrWrapper : public PatientsDeleteEndpointBaseWrapper
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
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct PatientDeleteEndpointMultipleEntitiesMgrWrapper : public PatientsDeleteEndpointBaseWrapper
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
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct PatientsDeleteEndpointNotExistingEntityWrapper : public PatientDeleteEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingPatient";
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::NOT_FOUND;
		}

		static bool getExpectedEntityDeletion()
		{
			return false;
		}
	};

	struct PatientsDeleteEndpointExceptionOnDeletionWrapper : public PatientDeleteEndpointMultipleEntitiesMgrWrapper
	{
		static bool getExceptionOnDeletion()
		{
			return true;
		}

		static systelab::web_server::Reply::StatusType getExpectedReplyStatus()
		{
			return systelab::web_server::Reply::INTERNAL_SERVER_ERROR;
		}

		static std::string getExpectedReplyContent()
		{
			return "{ \"exception\": \"Internal error\" }";
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};


	typedef ::testing::Types<
		PatientsDeleteEndpointEmptyMgrWrapper,
		PatientsDeleteEndpointSingleEntityMgrWrapper,
		PatientDeleteEndpointMultipleEntitiesMgrWrapper,
		PatientsDeleteEndpointNotExistingEntityWrapper,
		PatientsDeleteEndpointExceptionOnDeletionWrapper
	> PatientsDeleteEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsDeleteEndpointTest, EntityDeleteEndpointTest, PatientsDeleteEndpointWrappers);

}}