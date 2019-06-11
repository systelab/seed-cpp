#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/UserDbTranslator.h"
#include "SeedCppCore/Model/User.h"


using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct AdminUserWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setId(std::string("28D5A393-00EF-4F44-94C5-BCE453E209B8"));
			user.setLogin("jsmith");
			user.setPassword("p@ssw0rd");
			user.setName("John");
			user.setSurname("Smith");
			user.setRole(model::User::ADMIN_ROLE);
			user.setCreationTime(boost::posix_time::ptime(boost::gregorian::date(2017, 4, 15),
														  boost::posix_time::time_duration(20, 59, 55, 123)));
			user.setUpdateTime(boost::posix_time::ptime(boost::gregorian::date(2019, 6, 20),
														boost::posix_time::time_duration(0, 0, 0)));

			return user;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", std::string("28D5A393-00EF-4F44-94C5-BCE453E209B8")),
					  StubFieldValue("login", std::string("jsmith")),
					  StubFieldValue("password", std::string("p@ssw0rd")),
					  StubFieldValue("name", std::string("John")),
					  StubFieldValue("surname", std::string("Smith")),
					  StubFieldValue("role", static_cast<int>(model::User::ADMIN_ROLE)),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("20170415T205955.000123")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20190620T000000")),
					};
		}

		static std::unique_ptr<dal::UserDbTranslator> buildDbTranslator(model::User& entity)
		{
			return std::make_unique<dal::UserDbTranslator>(entity);
		}
	};


	typedef ::testing::Types<
		AdminUserWrapper/*,
		BasicUserWrapper*/
	> UserDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UserTranslatorTest, DatabaseTranslatorTest, UserDbTranslatorTestWrappers);

}}