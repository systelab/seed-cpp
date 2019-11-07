#include "stdafx.h"
#include "SeedCppCoreUnitTest/Tests/REST/Endpoints/EntityGetAllEndpointTest.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"
#include "SeedCppCore/REST/Endpoints/Allergies/AllergiesGetAllEndpoint.h"

#include "SeedCppCoreTestUtilities/Builders/AllergyBuilder.h"
#include "SeedCppCoreTestUtilities/Mocks/DAL/Translators/JSON/MockJSONSaveTranslator.h"


using namespace std::string_literals;
using namespace seed_cpp::test_utility;
using namespace testing;

namespace seed_cpp { namespace unit_test {

	struct AllergiesGetAllEndpointBaseWrapper
	{
		typedef model::Allergy ModelEntity;
		typedef model::AllergyMgr ModelManager;
		typedef rest::AllergiesGetAllEndpoint Endpoint;

		static std::map<std::string, std::string> getQueryStrings()
		{
			return {};
		}

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

	struct AllergiesGetAllEndpointEmptyWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
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

	struct AllergiesGetAllEndpointSingleEntityWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			return { AllergyBuilder().setId("Allergy1"s).getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy1\" }" << std::endl;
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

	struct AllergiesGetAllEndpointSinglePageWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			return { AllergyBuilder().setId("Allergy1"s).getEntity(),
					 AllergyBuilder().setId("Allergy2"s).getEntity(),
					 AllergyBuilder().setId("Allergy3"s).getEntity() };
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy1\" }," << std::endl;
			ss << "      { \"id\": \"Allergy2\" }," << std::endl;
			ss << "      { \"id\": \"Allergy3\" }" << std::endl;
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

	struct AllergiesGetAllEndpointFirstPageWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::vector<model::Allergy> getEntities()
		{
			std::vector<model::Allergy> allergies;
			for (unsigned int i = 1; i <= 96; i++)
			{
				allergies.push_back(AllergyBuilder().setId("Allergy" + std::to_string(i)).getEntity());
			}

			return allergies;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy1\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy2\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy3\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy4\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy5\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy6\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy7\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy8\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy9\"  }," << std::endl;
			ss << "      { \"id\": \"Allergy10\" }," << std::endl;
			ss << "      { \"id\": \"Allergy11\" }," << std::endl;
			ss << "      { \"id\": \"Allergy12\" }," << std::endl;
			ss << "      { \"id\": \"Allergy13\" }," << std::endl;
			ss << "      { \"id\": \"Allergy14\" }," << std::endl;
			ss << "      { \"id\": \"Allergy15\" }," << std::endl;
			ss << "      { \"id\": \"Allergy16\" }," << std::endl;
			ss << "      { \"id\": \"Allergy17\" }," << std::endl;
			ss << "      { \"id\": \"Allergy18\" }," << std::endl;
			ss << "      { \"id\": \"Allergy19\" }," << std::endl;
			ss << "      { \"id\": \"Allergy20\" }" << std::endl;
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

	struct AllergiesGetAllEndpointMidPageWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "1"} };
		}

		static std::vector<model::Allergy> getEntities()
		{
			std::vector<model::Allergy> allergies;
			for (unsigned int i = 1; i <= 67; i++)
			{
				allergies.push_back(AllergyBuilder().setId("Allergy" + std::to_string(i)).getEntity());
			}

			return allergies;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy21\" }," << std::endl;
			ss << "      { \"id\": \"Allergy22\" }," << std::endl;
			ss << "      { \"id\": \"Allergy23\" }," << std::endl;
			ss << "      { \"id\": \"Allergy24\" }," << std::endl;
			ss << "      { \"id\": \"Allergy25\" }," << std::endl;
			ss << "      { \"id\": \"Allergy26\" }," << std::endl;
			ss << "      { \"id\": \"Allergy27\" }," << std::endl;
			ss << "      { \"id\": \"Allergy28\" }," << std::endl;
			ss << "      { \"id\": \"Allergy29\" }," << std::endl;
			ss << "      { \"id\": \"Allergy30\" }," << std::endl;
			ss << "      { \"id\": \"Allergy31\" }," << std::endl;
			ss << "      { \"id\": \"Allergy32\" }," << std::endl;
			ss << "      { \"id\": \"Allergy33\" }," << std::endl;
			ss << "      { \"id\": \"Allergy34\" }," << std::endl;
			ss << "      { \"id\": \"Allergy35\" }," << std::endl;
			ss << "      { \"id\": \"Allergy36\" }," << std::endl;
			ss << "      { \"id\": \"Allergy37\" }," << std::endl;
			ss << "      { \"id\": \"Allergy38\" }," << std::endl;
			ss << "      { \"id\": \"Allergy39\" }," << std::endl;
			ss << "      { \"id\": \"Allergy40\" }" << std::endl;
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

	struct AllergiesGetAllEndpointLastPageWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "3"} };
		}

		static std::vector<model::Allergy> getEntities()
		{
			std::vector<model::Allergy> allergies;
			for (unsigned int i = 1; i <= 67; i++)
			{
				allergies.push_back(AllergyBuilder().setId("Allergy" + std::to_string(i)).getEntity());
			}

			return allergies;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy61\" }," << std::endl;
			ss << "      { \"id\": \"Allergy62\" }," << std::endl;
			ss << "      { \"id\": \"Allergy63\" }," << std::endl;
			ss << "      { \"id\": \"Allergy64\" }," << std::endl;
			ss << "      { \"id\": \"Allergy65\" }," << std::endl;
			ss << "      { \"id\": \"Allergy66\" }," << std::endl;
			ss << "      { \"id\": \"Allergy67\" }" << std::endl;
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

	struct AllergiesGetAllEndpointCustomPageSizeWrapper : public AllergiesGetAllEndpointBaseWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "2"}, {"size", "5"} };
		}

		static std::vector<model::Allergy> getEntities()
		{
			std::vector<model::Allergy> allergies;
			for (unsigned int i = 1; i <= 100; i++)
			{
				allergies.push_back(AllergyBuilder().setId("Allergy" + std::to_string(i)).getEntity());
			}

			return allergies;
		}

		static std::string getExpectedReplyContent()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "   \"content\": " << std::endl;
			ss << "   [" << std::endl;
			ss << "      { \"id\": \"Allergy11\" }," << std::endl;
			ss << "      { \"id\": \"Allergy12\" }," << std::endl;
			ss << "      { \"id\": \"Allergy13\" }," << std::endl;
			ss << "      { \"id\": \"Allergy14\" }," << std::endl;
			ss << "      { \"id\": \"Allergy15\" }"  << std::endl;
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

	struct AllergiesGetAllEndpointInvalidPageQueryStringWrapper : public AllergiesGetAllEndpointFirstPageWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"page", "invalid"} };
		}
	};

	struct AllergiesGetAllEndpointInvalidSizeQueryStringWrapper : public AllergiesGetAllEndpointFirstPageWrapper
	{
		static std::map<std::string, std::string> getQueryStrings()
		{
			return { {"size", "invalid"} };
		}
	};


	typedef ::testing::Types<
		AllergiesGetAllEndpointEmptyWrapper,
		AllergiesGetAllEndpointSingleEntityWrapper,
		AllergiesGetAllEndpointSinglePageWrapper,
		AllergiesGetAllEndpointFirstPageWrapper,
		AllergiesGetAllEndpointMidPageWrapper,
		AllergiesGetAllEndpointLastPageWrapper,
		AllergiesGetAllEndpointCustomPageSizeWrapper,
		AllergiesGetAllEndpointInvalidPageQueryStringWrapper,
		AllergiesGetAllEndpointInvalidSizeQueryStringWrapper
	> AllergiesGetAllEndpointWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergiesGetAllEndpointTest, EntityGetAllEndpointTest, AllergiesGetAllEndpointWrappers);

}}