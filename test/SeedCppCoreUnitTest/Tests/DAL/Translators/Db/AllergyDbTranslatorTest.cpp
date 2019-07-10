#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/AllergyDbTranslator.h"
#include "SeedCppCore/Model/Allergy.h"


using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct AllergyWrapper
	{
		typedef model::Allergy ModelEntity;

		static model::Allergy getEntity()
		{
			model::Allergy allergy;
			allergy.setId(std::string("49D8385E-4E41-49B1-9C55-B200879AEE4C"));
			allergy.setName("Tree Nuts");
			allergy.setSigns("Raised red bumps of skin");
			allergy.setSymptoms("Abdominal pain, cramps, nausea and vomiting");
			allergy.setCreationTime(boost::posix_time::ptime(boost::gregorian::date(2014, 3, 19),
														  boost::posix_time::time_duration(9, 15, 2, 321)));
			allergy.setUpdateTime(boost::posix_time::ptime(boost::gregorian::date(2019, 7, 10),
														boost::posix_time::time_duration(14, 5, 43)));

			return allergy;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", std::string("49D8385E-4E41-49B1-9C55-B200879AEE4C")),
					  StubFieldValue("name", std::string("Tree Nuts")),
					  StubFieldValue("signs", std::string("Raised red bumps of skin")),
					  StubFieldValue("symptoms", std::string("Abdominal pain, cramps, nausea and vomiting")),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("20140319T091502.000321")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20190710T140543")),
					};
		}

		static std::unique_ptr<dal::AllergyDbTranslator> buildDbTranslator(model::Allergy& entity)
		{
			return std::make_unique<dal::AllergyDbTranslator>(entity);
		}
	};


	typedef ::testing::Types<
		AllergyWrapper
	> AllergyDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AllergyTranslatorTest, DatabaseTranslatorTest, AllergyDbTranslatorTestWrappers);

}}