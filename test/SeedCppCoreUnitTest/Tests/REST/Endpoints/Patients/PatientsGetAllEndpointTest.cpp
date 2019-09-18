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

		static std::map<std::string, std::string> getQueryStrings()
		{
			return {};
		}

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

	struct PatientsGetAllEndpointSinglePageWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			return { PatientBuilder().setId("Patient1").getEntity(),
					 PatientBuilder().setId("Patient2").getEntity(),
					 PatientBuilder().setId("Patient3").getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient1\" }," << std::endl;
			ss << "      { \"id\": \"Patient2\" }," << std::endl;
			ss << "      { \"id\": \"Patient3\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 3," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 3," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 1" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct PatientsGetAllEndpointFirstPageWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::vector<model::Patient> getEntities()
		{
			std::vector<model::Patient> patients;
			for (unsigned int i = 1; i <= 96; i++)
			{
				patients.push_back(PatientBuilder().setId("Patient" + std::to_string(i)).getEntity());
			}

			return patients;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient1\"  }," << std::endl;
			ss << "      { \"id\": \"Patient2\"  }," << std::endl;
			ss << "      { \"id\": \"Patient3\"  }," << std::endl;
			ss << "      { \"id\": \"Patient4\"  }," << std::endl;
			ss << "      { \"id\": \"Patient5\"  }," << std::endl;
			ss << "      { \"id\": \"Patient6\"  }," << std::endl;
			ss << "      { \"id\": \"Patient7\"  }," << std::endl;
			ss << "      { \"id\": \"Patient8\"  }," << std::endl;
			ss << "      { \"id\": \"Patient9\"  }," << std::endl;
			ss << "      { \"id\": \"Patient10\" }," << std::endl;
			ss << "      { \"id\": \"Patient11\" }," << std::endl;
			ss << "      { \"id\": \"Patient12\" }," << std::endl;
			ss << "      { \"id\": \"Patient13\" }," << std::endl;
			ss << "      { \"id\": \"Patient14\" }," << std::endl;
			ss << "      { \"id\": \"Patient15\" }," << std::endl;
			ss << "      { \"id\": \"Patient16\" }," << std::endl;
			ss << "      { \"id\": \"Patient17\" }," << std::endl;
			ss << "      { \"id\": \"Patient18\" }," << std::endl;
			ss << "      { \"id\": \"Patient19\" }," << std::endl;
			ss << "      { \"id\": \"Patient20\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 96," << std::endl;
			ss << "   \"first\": true," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 0," << std::endl;
			ss << "   \"numberOfElements\": 20," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 5" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct PatientsGetAllEndpointMidPageWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "1"} };
		}

		static std::vector<model::Patient> getEntities()
		{
			std::vector<model::Patient> patients;
			for (unsigned int i = 1; i <= 67; i++)
			{
				patients.push_back(PatientBuilder().setId("Patient" + std::to_string(i)).getEntity());
			}

			return patients;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient21\" }," << std::endl;
			ss << "      { \"id\": \"Patient22\" }," << std::endl;
			ss << "      { \"id\": \"Patient23\" }," << std::endl;
			ss << "      { \"id\": \"Patient24\" }," << std::endl;
			ss << "      { \"id\": \"Patient25\" }," << std::endl;
			ss << "      { \"id\": \"Patient26\" }," << std::endl;
			ss << "      { \"id\": \"Patient27\" }," << std::endl;
			ss << "      { \"id\": \"Patient28\" }," << std::endl;
			ss << "      { \"id\": \"Patient29\" }," << std::endl;
			ss << "      { \"id\": \"Patient30\" }," << std::endl;
			ss << "      { \"id\": \"Patient31\" }," << std::endl;
			ss << "      { \"id\": \"Patient32\" }," << std::endl;
			ss << "      { \"id\": \"Patient33\" }," << std::endl;
			ss << "      { \"id\": \"Patient34\" }," << std::endl;
			ss << "      { \"id\": \"Patient35\" }," << std::endl;
			ss << "      { \"id\": \"Patient36\" }," << std::endl;
			ss << "      { \"id\": \"Patient37\" }," << std::endl;
			ss << "      { \"id\": \"Patient38\" }," << std::endl;
			ss << "      { \"id\": \"Patient39\" }," << std::endl;
			ss << "      { \"id\": \"Patient40\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 67," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 1," << std::endl;
			ss << "   \"numberOfElements\": 20," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 4" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct PatientsGetAllEndpointLastPageWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "3"} };
		}

		static std::vector<model::Patient> getEntities()
		{
			std::vector<model::Patient> patients;
			for (unsigned int i = 1; i <= 67; i++)
			{
				patients.push_back(PatientBuilder().setId("Patient" + std::to_string(i)).getEntity());
			}

			return patients;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient61\" }," << std::endl;
			ss << "      { \"id\": \"Patient62\" }," << std::endl;
			ss << "      { \"id\": \"Patient63\" }," << std::endl;
			ss << "      { \"id\": \"Patient64\" }," << std::endl;
			ss << "      { \"id\": \"Patient65\" }," << std::endl;
			ss << "      { \"id\": \"Patient66\" }," << std::endl;
			ss << "      { \"id\": \"Patient67\" }" << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 67," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": true," << std::endl;
			ss << "   \"number\": 3," << std::endl;
			ss << "   \"numberOfElements\": 7," << std::endl;
			ss << "   \"size\": 20," << std::endl;
			ss << "   \"totalPages\": 4" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};

	struct PatientsGetAllEndpointCustomPageSizeWrapper : public PatientsGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "2"}, {"size", "5"} };
		}

		static std::vector<model::Patient> getEntities()
		{
			std::vector<model::Patient> patients;
			for (unsigned int i = 1; i <= 100; i++)
			{
				patients.push_back(PatientBuilder().setId("Patient" + std::to_string(i)).getEntity());
			}

			return patients;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Patient11\" }," << std::endl;
			ss << "      { \"id\": \"Patient12\" }," << std::endl;
			ss << "      { \"id\": \"Patient13\" }," << std::endl;
			ss << "      { \"id\": \"Patient14\" }," << std::endl;
			ss << "      { \"id\": \"Patient15\" }"  << std::endl;
			ss << "   ]," << std::endl;
			ss << "   \"totalElements\": 100," << std::endl;
			ss << "   \"first\": false," << std::endl;
			ss << "   \"last\": false," << std::endl;
			ss << "   \"number\": 2," << std::endl;
			ss << "   \"numberOfElements\": 5," << std::endl;
			ss << "   \"size\": 5," << std::endl;
			ss << "   \"totalPages\": 20" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}
	};


	typedef ::testing::Types<
		PatientsGetAllEndpointEmptyWrapper,
		PatientsGetAllEndpointSingleEntityWrapper,
		PatientsGetAllEndpointSinglePageWrapper,
		PatientsGetAllEndpointFirstPageWrapper,
		PatientsGetAllEndpointMidPageWrapper,
		PatientsGetAllEndpointLastPageWrapper,
		PatientsGetAllEndpointCustomPageSizeWrapper
	> PatientsGetAllEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientsGetAllEndpointTest, EntityGetAllEndpointTest, PatientsGetAllEndpointWrappers);

}}