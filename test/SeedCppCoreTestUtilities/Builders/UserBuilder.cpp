#include "stdafx.h"
#include "UserBuilder.h"


namespace seed_cpp { namespace test_utility {

	UserBuilder::UserBuilder()
		:m_user()
	{
	}

	UserBuilder::~UserBuilder() = default;

	UserBuilder& UserBuilder::setId(const boost::optional<std::string>& id)
	{
		m_user.setId(id);
		return *this;
	}

	UserBuilder& UserBuilder::setCreationTime(const boost::posix_time::ptime& creationTime)
	{
		m_user.setCreationTime(creationTime);
		return *this;
	}

	UserBuilder& UserBuilder::setUpdateTime(const boost::posix_time::ptime& updateTime)
	{
		m_user.setUpdateTime(updateTime);
		return *this;
	}

	UserBuilder& UserBuilder::setSurname(const std::string& surname)
	{
		m_user.setSurname(surname);
		return *this;
	}

	UserBuilder& UserBuilder::setName(const std::string& name)
	{
		m_user.setName(name);
		return *this;
	}

	UserBuilder& UserBuilder::setLogin(const std::string& login)
	{
		m_user.setLogin(login);
		return *this;
	}

	UserBuilder& UserBuilder::setPassword(const std::string& password)
	{
		m_user.setPassword(password);
		return *this;
	}

	UserBuilder& UserBuilder::setRole(model::User::Role role)
	{
		m_user.setRole(role);
		return *this;
	}

	model::User UserBuilder::getEntity() const
	{
		return m_user;
	}

}}
