#include "stdafx.h"
#include "JSONTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/JSON/UserJSONTranslator.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace unit_test {

	struct AdminUserJSONSaveTranslatorWrapper : public JSONTranslatorTestWrapper
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

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"id\": \"28D5A393-00EF-4F44-94C5-BCE453E209B8\",\n"
					"    \"login\": \"jsmith\",\n"
					"    \"password\": \"p@ssw0rd\"\n"
					"    \"name\": \"John\"\n"
					"    \"surname\": \"Smith\"\n"
					"    \"role\": \"admin\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONSaveTranslator> buildJSONSaveTranslator(model::User& user)
		{
			return std::make_unique<dal::UserJSONSaveTranslator>(user);
		}
	};

	typedef ::testing::Types<
		AdminUserJSONSaveTranslatorWrapper
	> UserJSONTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UserJSONTranslatorTest, JSONTranslatorSaveTest, UserJSONTranslatorTestWrappers);

}}
