#include "stdafx.h"
#include "UserJSONTranslator.h"

#include "Model/User.h"


namespace seed_cpp { namespace dal {

	UserJSONSaveTranslator::UserJSONSaveTranslator(const model::User &user)
		:m_user(user)
	{
	}

	UserJSONSaveTranslator::~UserJSONSaveTranslator() = default;

	void UserJSONSaveTranslator::saveEntityToJSON(systelab::json::IJSONValue& jsonUser) const
	{
		jsonUser.setType(systelab::json::OBJECT_TYPE);
		jsonUser.addMember("id", *m_user.getId());
		jsonUser.addMember("surname", m_user.getSurname());
		jsonUser.addMember("name", m_user.getName());
		jsonUser.addMember("login", m_user.getLogin());
		jsonUser.addMember("password", m_user.getPassword());
		jsonUser.addMember("role", translateRoleToString(m_user.getRole()));
	}

	std::string UserJSONSaveTranslator::translateRoleToString(model::User::Role role) const
	{
		if (role == model::User::ADMIN_ROLE)
		{
			return "admin";
		}
		else if (role == model::User::USER_ROLE)
		{
			return "user";
		}
		else
		{
			throw std::runtime_error("Unknown role");
		}
	}

	UserJSONLoadTranslator::UserJSONLoadTranslator(model::User& user)
		:m_user(user)
	{
	}

	UserJSONLoadTranslator::~UserJSONLoadTranslator() = default;

	void UserJSONLoadTranslator::loadEntityFromJSON(const systelab::json::IJSONValue& jsonUser)
	{
		if (jsonUser.hasObjectMember("surname"))
		{
			std::string surname = jsonUser.getObjectMemberValue("surname").getString();
			m_user.setSurname(surname);
		}

		if (jsonUser.hasObjectMember("name"))
		{
			std::string name = jsonUser.getObjectMemberValue("name").getString();
			m_user.setName(name);
		}

		if (jsonUser.hasObjectMember("login"))
		{
			std::string login = jsonUser.getObjectMemberValue("login").getString();
			m_user.setLogin(login);
		}

		if (jsonUser.hasObjectMember("password"))
		{
			std::string password = jsonUser.getObjectMemberValue("password").getString();
			m_user.setPassword(password);
		}

		if (jsonUser.hasObjectMember("role"))
		{
			std::string roleStr = jsonUser.getObjectMemberValue("role").getString();
			model::User::Role role = translateStringToRole(roleStr);
			m_user.setRole(role);
		}
	}

	model::User::Role UserJSONLoadTranslator::translateStringToRole(const std::string &role) const
	{
		if (role == "admin")
		{
			return model::User::ADMIN_ROLE;
		}
		else if (role == "user")
		{
			return model::User::USER_ROLE;
		}
		else
		{
			throw std::string("Unknown role");
		}
	}

}}
