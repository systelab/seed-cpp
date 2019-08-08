#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/UserDbTranslator.h"
#include "SeedCppCore/Model/User.h"


using namespace std::string_literals;
using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct UserBaseWrapper
	{
		typedef model::User ModelEntity;

		static std::unique_ptr<dal::UserDbTranslator> buildDbTranslator(model::User& entity)
		{
			return std::make_unique<dal::UserDbTranslator>(entity);
		}
	};

	struct AdminUserWrapper : public UserBaseWrapper
	{
		static model::User getEntity()
		{
			model::User user;
			user.setId("28D5A393-00EF-4F44-94C5-BCE453E209B8"s);
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
			return	{ StubFieldValue("id", "28D5A393-00EF-4F44-94C5-BCE453E209B8"s),
					  StubFieldValue("login", "jsmith"s),
					  StubFieldValue("password", "p@ssw0rd"s),
					  StubFieldValue("name", "John"s),
					  StubFieldValue("surname", "Smith"s),
					  StubFieldValue("role", static_cast<int>(model::User::ADMIN_ROLE)),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("20170415T205955.000123")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20190620T000000")),
					};
		}
	};

	struct BasicUserWrapper : public UserBaseWrapper
	{
		static model::User getEntity()
		{
			model::User user;
			user.setId("BB65526F-3110-400F-98E8-77AD289C2175"s);
			user.setLogin("agarcia");
			user.setPassword("M123456p");
			user.setName("Alex");
			user.setSurname("Garcia");
			user.setRole(model::User::USER_ROLE);
			user.setCreationTime(boost::posix_time::ptime(boost::gregorian::date(2015, 3, 14),
														  boost::posix_time::time_duration(8, 1, 2, 345)));
			user.setUpdateTime(boost::posix_time::ptime(boost::gregorian::date(2018, 5, 19),
														boost::posix_time::time_duration(1, 2, 3)));

			return user;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", "BB65526F-3110-400F-98E8-77AD289C2175"s),
					  StubFieldValue("login", "agarcia"s),
					  StubFieldValue("password", "M123456p"s),
					  StubFieldValue("name", "Alex"s),
					  StubFieldValue("surname", "Garcia"s),
					  StubFieldValue("role", static_cast<int>(model::User::USER_ROLE)),
					  StubFieldValue("creationTime", boost::posix_time::from_iso_string("20150314T080102.000345")),
					  StubFieldValue("updateTime", boost::posix_time::from_iso_string("20180519T010203")),
			};
		}
	};


	typedef ::testing::Types<
		AdminUserWrapper,
		BasicUserWrapper
	> UserDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UserTranslatorTest, DatabaseTranslatorTest, UserDbTranslatorTestWrappers);

}}