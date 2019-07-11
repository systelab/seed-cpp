#include "stdafx.h"
#include "AddressBuilder.h"


namespace seed_cpp { namespace test_utility {

	AddressBuilder::AddressBuilder()
		:m_address()
	{
	}

	AddressBuilder::~AddressBuilder() = default;

	AddressBuilder& AddressBuilder::setId(const boost::optional<unsigned int>& id)
	{
		m_address.setId(id);
		return *this;
	}

	AddressBuilder& AddressBuilder::setCoordinates(const std::string& coordinates)
	{
		m_address.setCoordinates(coordinates);
		return *this;
	}

	AddressBuilder& AddressBuilder::setStreet(const std::string& street)
	{
		m_address.setStreet(street);
		return *this;
	}

	AddressBuilder& AddressBuilder::setCity(const std::string& city)
	{
		m_address.setCity(city);
		return *this;
	}

	AddressBuilder& AddressBuilder::setZip(const std::string& zip)
	{
		m_address.setZip(zip);
		return *this;
	}

	model::Address AddressBuilder::getEntity() const
	{
		return m_address;
	}

}}
