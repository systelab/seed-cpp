#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace db_test {

	class EditUserCommand : public ICommand
	{
	public:
		EditUserCommand(const model::User&);
		virtual ~EditUserCommand();

		void execute(Core&) override;

	protected:
		std::unique_ptr<model::User> m_user;
	};

}}
