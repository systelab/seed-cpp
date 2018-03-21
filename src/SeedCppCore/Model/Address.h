#pragma once

#include <string>
#include <boost/optional.hpp>


namespace seed_cpp { namespace model {

	class Address
	{
	public:
		Address();
		Address(const Address&);
		virtual ~Address();

		boost::optional<unsigned int> getId() const;
		std::string getCoordinates() const;
		std::string getStreet() const;
		std::string getCity() const;
		std::string getZip() const;

		void setId(const boost::optional<unsigned int>&);
		void setCoordinates(const std::string&);
		void setStreet(const std::string&);
		void setCity(const std::string&);
		void setZip(const std::string&);

	private:
		boost::optional<unsigned int> m_id;
		std::string m_coordinates;
		std::string m_street;
		std::string m_city;
		std::string m_zip;
	};

}}
