#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/PatientDbTranslator.h"
#include "SeedCppCore/Model/Patient.h"


using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct PatientWrapper
	{
		typedef model::Patient ModelEntity;

		static model::Patient getEntity()
		{
			model::Patient patient;
			patient.setId(std::string("28D5A393-00EF-4F44-94C5-BCE453E209B8"));
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
			return	{ StubFieldValue("id", std::string("28D5A393-00EF-4F44-94C5-BCE453E209B8")),
					  StubFieldValue("name", std::string("George")),
					  StubFieldValue("surname", std::string("Orwell")),
					  StubFieldValue("dob", boost::posix_time::from_iso_string("19841213T000000")),
					  StubFieldValue("email", std::string("gorwell@gmail.com")),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("19900707T101500")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20190102T153000")),
					};
		}

		static std::unique_ptr<dal::PatientDbTranslator> buildDbTranslator(model::Patient& entity)
		{
			return std::make_unique<dal::PatientDbTranslator>(entity);
		}
	};


	typedef ::testing::Types<
		PatientWrapper
	> PatientDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(PatientTranslatorTest, DatabaseTranslatorTest, PatientDbTranslatorTestWrappers);

}}