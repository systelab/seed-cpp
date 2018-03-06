#include "StdAfx.h"
#include "Patient.h"

#include "Address.h"


namespace seed_cpp { namespace model {

	Patient::Patient()
		:m_id()
		,m_surname("")
		,m_name("")
		,m_email("")
		,m_dob()
		,m_address(new Address())
	{
	}

	Patient::~Patient()
	{
	}

	boost::optional<unsigned int> Patient::getId() const
	{
		return m_id;
	}

	std::string Patient::getSurname() const
	{
		return m_surname;
	}

	std::string Patient::getName() const
	{
		return m_name;
	}

	std::string Patient::getEmail() const
	{
		return m_email;
	}

	boost::posix_time::ptime Patient::getDob() const
	{
		return m_dob;
	}

	Address& Patient::getAddress() const
	{
		return *m_address;
	}

	void Patient::setId(const boost::optional<unsigned int>& id)
	{
		m_id = id;
	}

	void Patient::setSurname(const std::string& surname)
	{
		m_surname = surname;
	}

	void Patient::setName(const std::string& name)
	{
		m_name = name;
	}

	void Patient::setEmail(const std::string& email)
	{
		m_email = email;
	}

	void Patient::setDob(const boost::posix_time::ptime& dob)
	{
		m_dob = dob;
	}

	void Patient::setAddress(std::unique_ptr<Address> address)
	{
		m_address = std::move(address);
	}

}}
