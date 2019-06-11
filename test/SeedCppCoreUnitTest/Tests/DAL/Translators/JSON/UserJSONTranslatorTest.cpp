#include "stdafx.h"
#include "JSONTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/JSON/UserJSONTranslator.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace unit_test {

	// Tests for save translator
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
					"    \"password\": \"p@ssw0rd\",\n"
					"    \"name\": \"John\",\n"
					"    \"surname\": \"Smith\",\n"
					"    \"role\": \"admin\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONSaveTranslator> buildJSONSaveTranslator(model::User& user)
		{
			return std::make_unique<dal::UserJSONSaveTranslator>(user);
		}
	};

	struct BasicUserJSONSaveTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setId(std::string("DB674E71-92D4-4B63-A068-71FE79BE381B"));
			user.setLogin("pdalhstrom");
			user.setPassword("SuperDaddy");
			user.setName("Peter");
			user.setSurname("Dahlstrom");
			user.setRole(model::User::USER_ROLE);

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
				"    \"id\": \"DB674E71-92D4-4B63-A068-71FE79BE381B\",\n"
				"    \"login\": \"pdalhstrom\",\n"
				"    \"password\": \"SuperDaddy\",\n"
				"    \"name\": \"Peter\",\n"
				"    \"surname\": \"Dahlstrom\",\n"
				"    \"role\": \"user\"\n"
				"}";
		}

		static std::unique_ptr<dal::IJSONSaveTranslator> buildJSONSaveTranslator(model::User& user)
		{
			return std::make_unique<dal::UserJSONSaveTranslator>(user);
		}
	};

	typedef ::testing::Types<
		AdminUserJSONSaveTranslatorWrapper,
		BasicUserJSONSaveTranslatorWrapper
	> UserJSONSaveTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UserJSONTranslatorTest, JSONTranslatorSaveTest, UserJSONSaveTranslatorTestWrappers);


	// Tests for load translator
	struct UserAllFieldsJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
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
					"    \"login\": \"jsmith\",\n"
					"    \"password\": \"p@ssw0rd\",\n"
					"    \"name\": \"John\",\n"
					"    \"surname\": \"Smith\",\n"
					"    \"role\": \"admin\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	struct UserSurnameFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setSurname("newsurname");

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"surname\": \"newsurname\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			user.setSurname("oldsurname");
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	struct UserNameFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setName("newname");

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"name\": \"newname\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			user.setName("oldname");
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	struct UserLoginFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setLogin("newlogin");

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
				"    \"login\": \"newlogin\"\n"
				"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			user.setLogin("oldlogin");
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	struct UserPasswordFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setPassword("newpassword");

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"password\": \"newpassword\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			user.setPassword("oldpassword");
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	struct UserRoleFieldJSONLoadTranslatorWrapper : public JSONTranslatorTestWrapper
	{
		typedef model::User ModelEntity;

		static model::User getEntity()
		{
			model::User user;
			user.setRole(model::User::Role::USER_ROLE);

			return user;
		}

		static std::string getJSONString()
		{
			return	"{\n"
					"    \"role\": \"user\"\n"
					"}";
		}

		static std::unique_ptr<dal::IJSONLoadTranslator> buildJSONLoadTranslator(model::User& user)
		{
			user.setRole(model::User::Role::ADMIN_ROLE);
			return std::make_unique<dal::UserJSONLoadTranslator>(user);
		}
	};

	typedef ::testing::Types<
		UserAllFieldsJSONLoadTranslatorWrapper,
		UserSurnameFieldJSONLoadTranslatorWrapper,
		UserNameFieldJSONLoadTranslatorWrapper,
		UserLoginFieldJSONLoadTranslatorWrapper,
		UserPasswordFieldJSONLoadTranslatorWrapper,
		UserRoleFieldJSONLoadTranslatorWrapper
	> UserJSONLoadTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(UserJSONTranslatorTest, JSONTranslatorLoadTest, UserJSONLoadTranslatorTestWrappers);

}}
