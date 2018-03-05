#pragma once

#include <string>


namespace seed_cpp { namespace model {

	class Address
	{
	public:
		Address();
		Address(const Address&);
		virtual ~Address();

		std::string getCoordinates() const;
		std::string getStreet() const;
		std::string getCity() const;
		std::string getZip() const;

		void setCoordinates(const std::string&);
		void setStreet(const std::string&);
		void setCity(const std::string&);
		void setZip(const std::string&);

	private:
		std::string m_coordinates;
		std::string m_street;
		std::string m_city;
		std::string m_zip;
	};

}}
