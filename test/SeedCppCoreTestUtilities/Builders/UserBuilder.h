#include "stdafx.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace test_utility {

	class UserBuilder
	{
	public:
		UserBuilder();
		virtual ~UserBuilder();

		UserBuilder& setId(const boost::optional<std::string>&);
		UserBuilder& setCreationTime(const boost::posix_time::ptime&);
		UserBuilder& setUpdateTime(const boost::posix_time::ptime&);
		UserBuilder& setSurname(const std::string&);
		UserBuilder& setName(const std::string&);
		UserBuilder& setLogin(const std::string&);
		UserBuilder& setPassword(const std::string&);
		UserBuilder& setRole(model::User::Role);

		model::User getEntity() const;

	private:
		model::User m_user;
	};

}}
