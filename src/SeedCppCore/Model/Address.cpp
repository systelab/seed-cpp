#include "StdAfx.h"
#include "Address.h"


namespace seed_cpp { namespace model {

	Address::Address()
		:m_id()
		,m_coordinates("")
		,m_street("")
		,m_city("")
		,m_zip("")
	{
	}

	Address::Address(const Address& other)
		:m_id(other.m_id)
		,m_coordinates(other.m_coordinates)
		,m_street(other.m_street)
		,m_city(other.m_city)
		,m_zip(other.m_zip)
	{
	}

	Address::~Address()
	{
	}

	boost::optional<unsigned int> Address::getId() const
	{
		return m_id;
	}

	std::string Address::getCoordinates() const
	{
		return m_coordinates;
	}

	std::string Address::getStreet() const
	{
		return m_street;
	}

	std::string Address::getCity() const
	{
		return m_city;
	}

	std::string Address::getZip() const
	{
		return m_zip;
	}

	void Address::setId(const boost::optional<unsigned int>& id)
	{
		m_id = id;
	}

	void Address::setCoordinates(const std::string& coordinates)
	{
		m_coordinates = coordinates;
	}

	void Address::setStreet(const std::string& street)
	{
		m_street = street;
	}

	void Address::setCity(const std::string& city)
	{
		m_city = city;
	}

	void Address::setZip(const std::string& zip)
	{
		m_zip = zip;
	}

}}
