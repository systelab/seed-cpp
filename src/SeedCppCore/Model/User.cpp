#include "StdAfx.h"
#include "User.h"


namespace seed_cpp { namespace model {

	User::User()
		:BaseEntity()
		,m_surname("")
		,m_name("")
		,m_login("")
		,m_password()
		,m_role(USER_ROLE)
	{
	}

	User::User(const User& other)
		:BaseEntity(other)
		,m_surname(other.m_surname)
		,m_name(other.m_name)
		,m_login(other.m_login)
		,m_password(other.m_password)
		,m_role(other.m_role)
	{
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

	User& User::operator= (const User& other)
	{
		BaseEntity::operator=(other);

		m_surname = other.m_surname;
		m_name = other.m_name;
		m_login = other.m_login;
		m_password = other.m_password;
		m_role = other.m_role;

		return *this;
	}

	bool operator== (const User& lhs, const User& rhs)
	{
		const auto& lhsBase = (const BaseEntity&) lhs;
		const auto& rhsBase = (const BaseEntity&) rhs;
		if (lhsBase != rhsBase)
		{
			return false;
		}

		if ( (lhs.m_surname != rhs.m_surname) ||
			 (lhs.m_name != rhs.m_name) ||
			 (lhs.m_login != rhs.m_login) ||
			 (lhs.m_password != rhs.m_password) ||
			 (lhs.m_role) != (rhs.m_role) )
		{
			return false;
		}

		return true;
	}

	bool operator!= (const User& lhs, const User& rhs)
	{
		return !(lhs == rhs);
	}

}}
