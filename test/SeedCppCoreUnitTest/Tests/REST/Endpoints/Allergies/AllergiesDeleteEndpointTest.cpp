#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityDeleteEndpointTest.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"
#include "SeedCppCore/REST/Endpoints/Allergies/AllergiesDeleteEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/AllergyBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/Services/Model/MockAllergyModelService.h"


using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct AllergiesDeleteEndpointBaseWrapper
	{
		typedef model::Allergy ModelEntity;
		typedef model::AllergyMgr ModelManager;
		typedef test_utility::MockAllergyModelService ModelEntityService;
		typedef rest::AllergiesDeleteEndpoint Endpoint;

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

	struct AllergiesDeleteEndpointEmptyMgrWrapper : public AllergiesDeleteEndpointBaseWrapper
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

		static bool getExpectedEntityDeletion()
		{
			return false;
		}
	};

	struct AllergiesDeleteEndpointSingleEntityMgrWrapper : public AllergiesDeleteEndpointBaseWrapper
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
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct AllergiesDeleteEndpointMultipleEntitiesMgrWrapper : public AllergiesDeleteEndpointBaseWrapper
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
			return systelab::web_server::Reply::NO_CONTENT;
		}

		static bool getExpectedEntityDeletion()
		{
			return true;
		}
	};

	struct AllergiesDeleteEndpointNotExistingEntityWrapper : public AllergiesDeleteEndpointMultipleEntitiesMgrWrapper
	{
		static std::string getIdentifierParameter()
		{
			return "NotExistingAllergy";
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

	struct AllergiesDeleteEndpointExceptionOnDeletionWrapper : public AllergiesDeleteEndpointMultipleEntitiesMgrWrapper
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
		AllergiesDeleteEndpointEmptyMgrWrapper,
		AllergiesDeleteEndpointSingleEntityMgrWrapper,
		AllergiesDeleteEndpointMultipleEntitiesMgrWrapper,
		AllergiesDeleteEndpointNotExistingEntityWrapper,
		AllergiesDeleteEndpointExceptionOnDeletionWrapper
	> AllergiesDeleteEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergiesDeleteEndpointTest, EntityDeleteEndpointTest, AllergiesDeleteEndpointWrappers);

}}