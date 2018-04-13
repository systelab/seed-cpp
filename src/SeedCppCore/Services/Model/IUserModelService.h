#pragma once

#include <string>


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class IUserModelService
	{
	public:
		virtual ~IUserModelService() {};

		virtual const model::User* getUserByLogin(const std::string&) const = 0;
	};

}}

