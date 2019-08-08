#include "stdafx.h"
#include "JSONTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/JSON/AllergyJSONTranslator.h"
#include "SeedCppCore/Model/Allergy.h"


namespace seed_cpp { namespace unit_test {

	// Tests for save translator
	struct AllergyJSONSaveTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setId(std::string("49D8385E-4E41-49B1-9C55-B200879AEE4C"));
			allergy.setName("Tree Nuts");
			allergy.setSigns("Raised red bumps of skin");
			allergy.setSymptoms("Abdominal pain, cramps, nausea and vomiting.");

			return allergy;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"id\": \"49D8385E-4E41-49B1-9C55-B200879AEE4C\",\n"
					"    \"name\": \"Tree Nuts\",\n"
					"    \"signs\": \"Raised red bumps of skin\",\n"
					"    \"symptoms\": \"Abdominal pain, cramps, nausea and vomiting.\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONSaveTranslator> buildJSONSaveTranslator(model::Allergy& allergy)
		{
			return std::make_unique<dal::AllergyJSONSaveTranslator>(allergy);
		}
	};

	typedef ::testing::Types<
		AllergyJSONSaveTranslatorWrapper
	> AllergyJSONSaveTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergyJSONTranslatorTest, JSONTranslatorSaveTest, AllergyJSONSaveTranslatorTestWrappers);


	// Tests for load translator
	struct AllergyAllFieldsJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setName("Tree Nuts");
			allergy.setSigns("Raised red bumps of skin");
			allergy.setSymptoms("Abdominal pain, cramps, nausea and vomiting");

			return allergy;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"name\": \"Tree Nuts\",\n"
					"    \"signs\": \"Raised red bumps of skin\",\n"
					"    \"symptoms\": \"Abdominal pain, cramps, nausea and vomiting\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Allergy& allergy)
		{
			return std::make_unique<dal::AllergyJSONLoadTranslator>(allergy);
		}
	};

	struct AllergyNameFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setName("newname");

			return allergy;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"name\": \"newname\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Allergy& allergy)
		{
			allergy.setName("oldname");
			return std::make_unique<dal::AllergyJSONLoadTranslator>(allergy);
		}
	};

	struct AllergySignsFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setSigns("newsigns");

			return allergy;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"signs\": \"newsigns\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Allergy& allergy)
		{
			allergy.setSigns("oldsigns");
			return std::make_unique<dal::AllergyJSONLoadTranslator>(allergy);
		}
	};

	struct AllergySymptomsFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setSymptoms("newsymptoms");

			return allergy;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"symptoms\": \"newsymptoms\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Allergy& allergy)
		{
			allergy.setSymptoms("oldsymptoms");
			return std::make_unique<dal::AllergyJSONLoadTranslator>(allergy);
		}
	};


	typedef ::testing::Types<
		AllergyAllFieldsJSONLoadTranslatorWrapper,
		AllergyNameFieldJSONLoadTranslatorWrapper,
		AllergySignsFieldJSONLoadTranslatorWrapper,
		AllergySymptomsFieldJSONLoadTranslatorWrapper
	> AllergyJSONLoadTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergyJSONTranslatorTest, JSONTranslatorLoadTest, AllergyJSONLoadTranslatorTestWrappers);

}}
