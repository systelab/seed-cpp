#include "stdafx.h"
#include "LoadPatientScenariosBuilder.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/AddressBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<LoadDatabaseTestData> LoadPatientScenariosBuilder::build()
	{
		// Single patient without address
		LoadDatabaseTestData scenarioPatientWithoutAddress;
		scenarioPatientWithoutAddress.m_sqlScripts = { "Database/Patients/PatientWithoutAddress.sql" };
		scenarioPatientWithoutAddress.m_expectedModel =
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

		// Single patient with address
		LoadDatabaseTestData scenarioPatientWithAddress;
		scenarioPatientWithAddress.m_sqlScripts = { "Database/Patients/PatientWithAddress.sql" };
		scenarioPatientWithAddress.m_expectedModel =
			ModelBuilder()
				.setPatients({
					PatientBuilder()
						.setId(std::string("1E751CF0-9C20-485E-B0A5-0BE754E74AD9"))
						.setName("Marc").setSurname("Robinson")
						.setDob(boost::posix_time::from_iso_string("19861004T102030"))
						.setEmail("marc@robinson.com")
						.setAddress(
							AddressBuilder()
								.setId(123456)
								.setCoordinates("12.344 N, 78.2323 W")
								.setStreet("C/Muntaner, 123 4t 1a")
								.setCity("Barcelona")
								.setZip("08080")
							.getEntity()
						)
						.setCreationTime(boost::posix_time::from_iso_string("20200927T091011"))
						.setUpdateTime(boost::posix_time::from_iso_string("20200927T121314"))
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

		return { scenarioPatientWithoutAddress, scenarioPatientWithoutAddress,
				 scenarioMassivePatients };
	}

}}

