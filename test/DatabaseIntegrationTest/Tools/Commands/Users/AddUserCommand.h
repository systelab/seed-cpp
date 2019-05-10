#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace db_test {

	class AddUserCommand : public ICommand
	{
	public:
		AddUserCommand(const model::User&);
		virtual ~AddUserCommand();

		void execute(Context&) override;

	protected:
		std::unique_ptr<model::User> m_user;
	};

}}