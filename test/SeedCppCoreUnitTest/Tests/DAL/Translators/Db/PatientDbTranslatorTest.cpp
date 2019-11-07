#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/PatientDbTranslator.h"
#include "SeedCppCore/Model/Patient.h"


using namespace std::string_literals;
using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct PatientBaseDbTranslatorWrapper
	{
		typedef model::Patient ModelEntity;

		static std::unique_ptr<dal::PatientDbTranslator> buildDbTranslator(model::Patient& entity)
		{
			return std::make_unique<dal::PatientDbTranslator>(entity);
		}
	};

	struct PatientWithDobDbTranslatorWrapper : public PatientBaseDbTranslatorWrapper
	{
		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setId("28D5A393-00EF-4F44-94C5-BCE453E209B8"s);
			patient.setName("George");
			patient.setSurname("Orwell");
			patient.setDob(boost::posix_time::ptime({1984, 12, 13}));
			patient.setEmail("gorwell@gmail.com");
			patient.setCreationTime(boost::posix_time::ptime(boost::gregorian::date(1990, 7, 7),
															 boost::posix_time::time_duration(10, 15, 00, 00)));
			patient.setUpdateTime(boost::posix_time::ptime(boost::gregorian::date(2019, 1, 2),
														   boost::posix_time::time_duration(15, 30, 0)));

			return patient;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", "28D5A393-00EF-4F44-94C5-BCE453E209B8"s),
					  StubFieldValue("name", "George"s),
					  StubFieldValue("surname", "Orwell"s),
					  StubFieldValue("dob", boost::posix_time::from_iso_string("19841213T000000")),
					  StubFieldValue("email", "gorwell@gmail.com"s),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("19900707T101500")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20190102T153000")),
					};
		}
	};

	struct PatientWithoutDobDbTranslatorWrapper : public PatientBaseDbTranslatorWrapper
	{
		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setId("D9E2EE73-85BD-451A-97FD-62D22F6E0B15"s);
			patient.setName("Charles");
			patient.setSurname("Dickens");
			patient.setEmail("cdickens@gmail.com");
			patient.setCreationTime(boost::posix_time::ptime(boost::gregorian::date(2018, 10, 4),
															 boost::posix_time::time_duration(13, 14, 15, 00)));
			patient.setUpdateTime(boost::posix_time::ptime(boost::gregorian::date(2018, 10, 5),
														   boost::posix_time::time_duration(16, 17, 18)));

			return patient;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", "D9E2EE73-85BD-451A-97FD-62D22F6E0B15"s),
					  StubFieldValue("name", "Charles"s),
					  StubFieldValue("surname", "Dickens"s),
					  StubFieldValue("dob"),
					  StubFieldValue("email", "cdickens@gmail.com"s),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("20181004T131415")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20181005T161718")),
			};
		}
	};


	typedef ::testing::Types<
		PatientWithDobDbTranslatorWrapper,
		PatientWithoutDobDbTranslatorWrapper
	> PatientDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientTranslatorTest, DatabaseTranslatorTest, PatientDbTranslatorTestWrappers);

}}