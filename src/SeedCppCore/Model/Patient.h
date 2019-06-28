#pragma once

#include "Model/Address.h"
#include "Model/BaseEntity.h"


namespace seed_cpp { namespace model {

	class Patient : public BaseEntity
	{
	public:
		Patient();
		Patient(const Patient&);
		virtual ~Patient() = default;

		std::string getSurname() const;
		std::string getName() const;
		std::string getEmail() const;
		boost::optional<boost::posix_time::ptime> getDob() const;
		Address& getAddress() const;

		void setSurname(const std::string&);
		void setName(const std::string&);
		void setEmail(const std::string&);
		void setDob(const boost::optional<boost::posix_time::ptime>&);
		void setAddress(std::unique_ptr<Address>);

		Patient &operator=(const Patient&);
		friend bool operator==(const Patient&, const Patient&);
		friend bool operator!=(const Patient&, const Patient&);

	private:
		std::string m_surname;
		std::string m_name;
		std::string m_email;
		boost::optional<boost::posix_time::ptime> m_dob;
		std::unique_ptr<Address> m_address;
	};

}}
