#include "stdafx.h"
#include "LoadPatientScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadDatabaseTestData> LoadPatientScenariosBuilder::build()
	{
		// Single patient
		LoadDatabaseTestData scenarioSinglePatient;
		scenarioSinglePatient.m_sqlScripts = { "Database/Patients/BasicPatients.sql" };
		scenarioSinglePatient.m_expectedModel =
			ModelBuilder()
				.setPatients({
					PatientBuilder()
						.setId(std::string("9055B141-3307-4868-9C81-D5722A5DC16D"))
						.setName("Ibai").setSurname("Parker")
						.setDob(boost::posix_time::from_iso_string("20100101T102030")).
						 setEmail("ibai@patata.com")
						.setCreationTime(boost::posix_time::from_iso_string("20190115T152318"))
						.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
					.getEntity()
				})
				.getEntity();

		// Massive patients
		LoadDatabaseTestData scenarioMassivePatients;
		
		scenarioMassivePatients.m_sqlScripts = { "Database/Patients/MassivePatients.sql" };

		std::vector<model::Patient> massivePatients;
		for (int i = 1; i <= 100; i++) 
		{
			std::stringstream ss;
			ss << "9055B141-3307-4868-9C81-D5722A5DC";
			ss << std::setw(3) << std::setfill('0') << i;
			std::string uuid = ss.str();

			massivePatients.push_back(
				PatientBuilder()
					.setId(uuid)
					.setName("Patient" + std::to_string(i)).setSurname("Werfen")
					.setDob(boost::posix_time::from_iso_string("20100101T102030"))
					.setEmail("noreply@werfen.com")
					.setCreationTime(boost::posix_time::from_iso_string("20190115T152318"))
					.setUpdateTime(boost::posix_time::from_iso_string("20190115T152318"))
				.getEntity()
			);
		}

		scenarioMassivePatients.m_expectedModel =
			ModelBuilder()
			.setPatients(massivePatients)
			.getEntity();


		return { scenarioSinglePatient, scenarioMassivePatients };
	}

}}

