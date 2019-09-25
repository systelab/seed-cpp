#include "stdafx.h"
#include "LoadAllergyScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/AllergyBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadDatabaseTestData> LoadAllergyScenariosBuilder::build()
	{
		// Allergy 1
		LoadDatabaseTestData scenarioNutsAllergy;
		scenarioNutsAllergy.m_sqlScripts = { "Database/Allergies/NutsAllergy.sql" };
		scenarioNutsAllergy.m_expectedModel =
			ModelBuilder().setAllergies({
				AllergyBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.setName("Tree Nuts")
					.setSigns("Raised red bumps of skin")
					.setSymptoms("Abdominal pain, cramps, nausea and vomiting")
					.getEntity(),
				}).getEntity();

		// Allergy 2
		LoadDatabaseTestData scenarioPollenAllergy;
		scenarioPollenAllergy.m_sqlScripts = { "Database/Allergies/PollenAllergy.sql" };
		scenarioPollenAllergy.m_expectedModel =
			ModelBuilder().setAllergies({
				AllergyBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D3"))
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093044"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152319"))
					.setName("Tree Pollen")
					.setSigns("Watery eyes")
					.setSymptoms("Sneezing, headaches")
					.getEntity(),
				}).getEntity();

		//Allergy 1 + Allergy 2
		LoadDatabaseTestData scenarioNutAndPollenAllergies;
		scenarioNutAndPollenAllergies.m_sqlScripts = {  "Database/Allergies/NutsAllergy.sql",
														"Database/Allergies/PollenAllergy.sql" };
		scenarioNutAndPollenAllergies.m_expectedModel =
			ModelBuilder().setAllergies({
				AllergyBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D4"))
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093045"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.setName("Tree Nuts")
					.setSigns("Raised red bumps of skin")
					.setSymptoms("Abdominal pain, cramps, nausea and vomiting")
					.getEntity(),
				AllergyBuilder()
					.setId(std::string("73A800FC-621C-4D94-A1A4-0B39075458D3"))
					.setCreationTime(boost::posix_time::from_iso_string("20170212T093044"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152319"))
					.setName("Tree Pollen")
					.setSigns("Watery eyes")
					.setSymptoms("Sneezing, headaches")
					.getEntity(),
				}).getEntity();


		return { scenarioNutsAllergy, scenarioPollenAllergy, scenarioNutAndPollenAllergies };
	}

}}