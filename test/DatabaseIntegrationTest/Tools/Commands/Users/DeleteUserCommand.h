#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace db_test {

	class DeleteUserCommand : public ICommand
	{
	public:
		DeleteUserCommand(const std::string&);
		virtual ~DeleteUserCommand();

		void execute(Context&) override;

	protected:
		std::string m_userId;
	};

}}
