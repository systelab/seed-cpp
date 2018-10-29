#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/optional.hpp>
#include <string>


namespace seed_cpp { namespace model {

	class Address;

	class Patient
	{
	public:
		Patient();
		Patient(const Patient&);
		virtual ~Patient();

		boost::optional<std::string> getId() const;
		std::string getSurname() const;
		std::string getName() const;
		std::string getEmail() const;
		boost::posix_time::ptime getDob() const;
		Address& getAddress() const;

		void setId(const boost::optional<std::string>&);
		void setSurname(const std::string&);
		void setName(const std::string&);
		void setEmail(const std::string&);
		void setDob(const boost::posix_time::ptime&);
		void setAddress(std::unique_ptr<Address>);

	private:
		boost::optional<std::string> m_id;
		std::string m_surname;
		std::string m_name;
		std::string m_email;
		boost::posix_time::ptime m_dob;
		std::unique_ptr<Address> m_address;
	};

}}
