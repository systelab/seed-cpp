#include "StdAfx.h"
#include "User.h"

#include "Address.h"


namespace seed_cpp { namespace model {

	User::User()
		:m_id()
		,m_surname("")
		,m_name("")
		,m_login("")
		,m_password()
		,m_role(USER_ROLE)
	{
	}

	User::~User()
	{
	}

	boost::optional<std::string> User::getId() const
	{
		return m_id;
	}

	std::string User::getSurname() const
	{
		return m_surname;
	}

	std::string User::getName() const
	{
		return m_name;
	}

	std::string User::getLogin() const
	{
		return m_login;
	}

	std::string User::getPassword() const
	{
		return m_password;
	}

	User::Role User::getRole() const
	{
		return m_role;
	}

	void User::setId(const boost::optional<std::string>& id)
	{
		m_id = id;
	}

	void User::setSurname(const std::string& surname)
	{
		m_surname = surname;
	}

	void User::setName(const std::string& name)
	{
		m_name = name;
	}

	void User::setLogin(const std::string& login)
	{
		m_login = login;
	}

	void User::setPassword(const std::string& password)
	{
		m_password = password;
	}

	void User::setRole(Role role)
	{
		m_role = role;
	}

}}
