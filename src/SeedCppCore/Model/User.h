#pragma once

#include "SeedCppCore/Model/BaseEntity.h"

#include <string>


namespace seed_cpp { namespace model {

	class User : public BaseEntity
	{
	public:
		enum Role
		{
			USER_ROLE = 0,
			ADMIN_ROLE = 1
		};

	public:
		User();
		User(const User&);
		virtual ~User() = default;

		std::string getSurname() const;
		std::string getName() const;
		std::string getLogin() const;
		std::string getPassword() const;
		Role getRole() const;

		void setSurname(const std::string&);
		void setName(const std::string&);
		void setLogin(const std::string&);
		void setPassword(const std::string&);
		void setRole(Role);

		User& operator= (const User&);
		friend bool operator== (const User&, const User&);
		friend bool operator!= (const User&, const User&);

	private:
		std::string m_surname;
		std::string m_name;
		std::string m_login;
		std::string m_password;
		Role m_role;
	};

}}
