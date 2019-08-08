#include "stdafx.h"
#include "JSONTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/JSON/PatientJSONTranslator.h"
#include "SeedCppCore/Model/Patient.h"


namespace seed_cpp { namespace unit_test {

	// Tests for save translator
	struct PatientJSONSaveTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setId(std::string("CC596235-86BE-46D6-A207-FC918BF208FD"));
			patient.setName("John");
			patient.setSurname("Smith");
			patient.setEmail("jsmith@hotmail.com");
			patient.setDob(boost::posix_time::ptime({ 1979, 12, 25 },
													boost::posix_time::time_duration(12, 15, 00, 00)));

			auto address = std::make_unique<model::Address>();
			address->setCoordinates("41.403796, 2.067094");
			address->setStreet("Avda. Josep Tarradelles, 231 7e A");
			address->setCity("Barcelona");
			address->setZip("08080");
			patient.setAddress(std::move(address));

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"id\": \"CC596235-86BE-46D6-A207-FC918BF208FD\",\n"
					"    \"name\": \"John\",\n"
					"    \"surname\": \"Smith\",\n"
					"    \"email\": \"jsmith@hotmail.com\",\n"
					"    \"dob\": \"1979-12-25T12:15:00\",\n"
					"    \"address\":\n"
					"    {\n"
					"        \"coordinates\": \"41.403796, 2.067094\",\n"
					"        \"street\": \"Avda. Josep Tarradelles, 231 7e A\",\n"
					"        \"city\": \"Barcelona\",\n"
					"        \"zip\": \"08080\"\n"
					"    }\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONSaveTranslator> buildJSONSaveTranslator(model::Patient& patient)
		{
			return std::make_unique<dal::PatientJSONSaveTranslator>(patient);
		}
	};

	typedef ::testing::Types<
		PatientJSONSaveTranslatorWrapper
	> PatientJSONSaveTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientJSONTranslatorTest, JSONTranslatorSaveTest, PatientJSONSaveTranslatorTestWrappers);


	// Tests for load translator
	struct PatientAllFieldsJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setName("John");
			patient.setSurname("Smith");
			patient.setEmail("jsmith@hotmail.com");
			patient.setDob(boost::posix_time::ptime({ 1979, 12, 25 },
													boost::posix_time::time_duration(12, 15, 00, 00)));

			auto address = std::make_unique<model::Address>();
			address->setCoordinates("41.403796, 2.067094");
			address->setStreet("Avda. Josep Tarradelles, 231 7e A");
			address->setCity("Barcelona");
			address->setZip("08080");
			patient.setAddress(std::move(address));

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"name\": \"John\",\n"
					"    \"surname\": \"Smith\",\n"
					"    \"email\": \"jsmith@hotmail.com\",\n"
					"    \"password\": \"p@ssw0rd\",\n"
					"    \"dob\": \"1979-12-25T12:15:00\",\n"
					"    \"address\":\n"
					"    {\n"
					"        \"coordinates\": \"41.403796, 2.067094\",\n"
					"        \"street\": \"Avda. Josep Tarradelles, 231 7e A\",\n"
					"        \"city\": \"Barcelona\",\n"
					"        \"zip\": \"08080\"\n"
					"    }"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	struct PatientNameFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setName("newname");

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"name\": \"newname\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			patient.setName("oldname");
			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	struct PatientSurnameFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setSurname("newsurname");

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"surname\": \"newsurname\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			patient.setSurname("oldsurname");
			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	struct PatientEmailFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setEmail("pepe@paco.com");

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"email\": \"pepe@paco.com\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			patient.setEmail("kiko@sete.com");
			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	struct PatientDobFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setDob(boost::posix_time::ptime({ 1980, 7, 21 },
													boost::posix_time::time_duration(11, 12, 13, 123456)));

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"dob\": \"1980-07-21T11:12:13.123456\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			patient.setDob(boost::posix_time::ptime({ 1955, 9, 11 },
													boost::posix_time::time_duration(17, 14, 00, 654321)));
			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	struct PatientAddressFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			auto address = std::make_unique<model::Address>();
			address->setCoordinates("newCoordinates");
			address->setStreet("newStreet");
			address->setCity("newCity");
			address->setZip("newZip");

			model::Patient patient;
			patient.setAddress(std::move(address));

			return patient;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"address\":\n"
					"    {\n"
					"        \"coordinates\": \"newCoordinates\",\n"
					"        \"street\": \"newStreet\",\n"
					"        \"city\": \"newCity\",\n"
					"        \"zip\": \"newZip\"\n"
					"    }\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::Patient& patient)
		{
			auto address = std::make_unique<model::Address>();
			address->setCoordinates("oldCoordinates");
			address->setStreet("oldStreet");
			address->setCity("oldCity");
			address->setZip("oldZip");
			patient.setAddress(std::move(address));

			return std::make_unique<dal::PatientJSONLoadTranslator>(patient);
		}
	};

	typedef ::testing::Types<
		PatientAllFieldsJSONLoadTranslatorWrapper,
		PatientNameFieldJSONLoadTranslatorWrapper,
		PatientSurnameFieldJSONLoadTranslatorWrapper,
		PatientEmailFieldJSONLoadTranslatorWrapper,
		PatientDobFieldJSONLoadTranslatorWrapper,
		PatientAddressFieldJSONLoadTranslatorWrapper
	> PatientJSONLoadTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientJSONTranslatorTest, JSONTranslatorLoadTest, PatientJSONLoadTranslatorTestWrappers);

}}
