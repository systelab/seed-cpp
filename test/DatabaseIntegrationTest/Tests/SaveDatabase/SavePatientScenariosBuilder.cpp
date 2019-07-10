#include "stdafx.h"
#include "SavePatientScenariosBuilder.h"
#include "Tools/Commands/Patients/AddPatientCommand.h"
//#include "Tools/Commands/Users/EditUserCommand.h"
#include "Tools/Commands/Patients/DeletePatientCommand.h"

#include "SeedCppCoreTestUtilities/Builders/ModelBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/PatientBuilder.h"
#include "SeedCppCoreTestUtilities/Builders/AddressBuilder.h"


using namespace seed_cpp::test_utility;

namespace seed_cpp { namespace db_test {

	std::vector<SaveDatabaseTestData> SavePatientScenariosBuilder::build()
	{
		// Add some users
		SaveDatabaseTestData scenarioAddPatient;
		scenarioAddPatient.setSQLScripts({});
		scenarioAddPatient.addCommand(std::make_unique<AddPatientCommand>(
			PatientBuilder()
				.setId(std::string("B08BFF46-6AA8-4558-9CD5-0B6EB8C4B768"))
				.setName("Phil").setSurname("Collins")
				.setEmail("qa@Collins.com")
				.setDob(boost::posix_time::ptime({1993,7,26}))
				.setCreationTime(boost::posix_time::from_iso_string("20150405T112133"))
				.setUpdateTime(boost::posix_time::from_iso_string("20190523T220314"))
				.setAddress(
					AddressBuilder()
						.setCoordinates("Cas9c7ascb")
						.setStreet("Av.Can Montcau 07")
						.setCity("Lliça d'Amunt")
						.setZip("08186")
					.getEntity()
				)
			.getEntity()
		));


		// Delete existing user
		SaveDatabaseTestData scenarioDeletePatient;
		scenarioDeletePatient.setSQLScripts({"Database/Patients/BasicPatients.sql"});
		scenarioDeletePatient.addCommand(std::make_unique<DeletePatientCommand>(std::string ("9055B141-3307-4868-9C81-D5722A5DC16D")));

		// Complex scenario
		SaveDatabaseTestData scenarioComplex;
		scenarioComplex.setSQLScripts({ "Database/Patients/BasicPatients.sql" });
		scenarioComplex.addCommand(std::make_unique<AddPatientCommand>(
			PatientBuilder()
			.setId(std::string("B08BFF46-6AA8-4558-9CD5-0B6EB8C4B768"))
			.setName("Phil").setSurname("Collins")
			.setEmail("qa@Collins.com")
			.setDob(boost::posix_time::ptime({ 1993,7,26 }))
			.setCreationTime(boost::posix_time::from_iso_string("20150405T112133"))
			.setUpdateTime(boost::posix_time::from_iso_string("20190523T220314"))
			.setAddress(
				AddressBuilder()
				.setCoordinates("Cas9c7ascb")
				.setStreet("Av.Can Montcau 07")
				.setCity("Lliça d'Amunt")
				.setZip("08186")
				.getEntity()
			)
			.getEntity()
		));
		scenarioComplex.addCommand(std::make_unique<AddPatientCommand>(
			PatientBuilder()
			.setId(std::string("52EA2C84-1AEC-4DFA-AF1A-5BFF6A231437"))
			.setName("Michael").setSurname("Douglas")
			.setEmail("michael@hotmail.com")
			.setDob(boost::posix_time::ptime({ 1960,5, 10 }))
			.setCreationTime(boost::posix_time::from_iso_string("19980506T130000"))
			.setUpdateTime(boost::posix_time::from_iso_string("19980506T130000"))
			.setAddress(
				AddressBuilder()
				.setCoordinates("ES123, BWS4324")
				.setStreet("150th Street")
				.setCity("Los Angeles")
				.setZip("P23341")
				.getEntity()
			)
			.getEntity()
		));
		scenarioComplex.addCommand(std::make_unique<DeletePatientCommand>(std::string("9055B141-3307-4868-9C81-D5722A5DC16D")));

		return { scenarioAddPatient, scenarioDeletePatient, scenarioComplex };
	}

}}
