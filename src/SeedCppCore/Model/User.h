#pragma once

#include <boost/optional.hpp>
#include <string>


namespace seed_cpp { namespace model {

	class User
	{
	public:
		enum Role
		{
			USER_ROLE = 0,
			ADMIN_ROLE = 1
		};

	public:
		User();
		virtual ~User();

		boost::optional<unsigned int> getId() const;
		std::string getSurname() const;
		std::string getName() const;
		std::string getLogin() const;
		std::string getPassword() const;
		Role getRole() const;

		void setId(const boost::optional<unsigned int>&);
		void setSurname(const std::string&);
		void setName(const std::string&);
		void setLogin(const std::string&);
		void setPassword(const std::string&);
		void setRole(Role);

	private:
		boost::optional<unsigned int> m_id;
		std::string m_surname;
		std::string m_name;
		std::string m_login;
		std::string m_password;
		Role m_role;
	};

}}
