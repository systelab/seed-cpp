#include "stdafx.h"
#include "Patient.h"

#include "Address.h"


namespace seed_cpp { namespace model {

	Patient::Patient()
		:BaseEntity()
		,m_surname("")
		,m_name("")
		,m_email("")
		,m_dob(boost::none)
		,m_address(std::make_unique<Address>())
	{
	}

	Patient::Patient(const Patient& other)
		:BaseEntity(other)
		,m_surname(other.m_surname)
		,m_name(other.m_name)
		,m_email(other.m_email)
		,m_dob(other.m_dob)
		,m_address(std::make_unique<Address>(*other.m_address))
	{
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

	boost::optional<boost::posix_time::ptime> Patient::getDob() const
	{
		return m_dob;
	}

	Address& Patient::getAddress() const
	{
		return *m_address;
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

	void Patient::setDob(const boost::optional<boost::posix_time::ptime>& dob)
	{
		m_dob = dob;
	}

	void Patient::setAddress(std::unique_ptr<Address> address)
	{
		m_address = std::move(address);
	}

	Patient& Patient::operator= (const Patient& other)
	{
		BaseEntity::operator=(other);

		m_surname = other.m_surname;
		m_name = other.m_name;
		m_email = other.m_email;
		m_dob = other.m_dob;
		*m_address = *other.m_address;

		return *this;
	}

	bool operator== (const Patient& lhs, const Patient& rhs)
	{
		const auto& lhsBase = (const BaseEntity&) lhs;
		const auto& rhsBase = (const BaseEntity&) rhs;
		if (lhsBase != rhsBase)
		{
			return false;
		}

		if ( (lhs.m_surname != rhs.m_surname) ||
			 (lhs.m_name != rhs.m_name) ||
			 (lhs.m_email != rhs.m_email) ||
			 (lhs.m_dob != rhs.m_dob) ||
			 (*lhs.m_address) != (*rhs.m_address) )
		{
			return false;
		}

		return true;
	}

	bool operator!= (const Patient& lhs, const Patient& rhs)
	{
		return !(lhs == rhs);
	}

}}
