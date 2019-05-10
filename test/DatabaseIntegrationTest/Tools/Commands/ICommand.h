#pragma once


namespace seed_cpp { namespace db_test {

	class Context;

	class ICommand
	{
	public:
		virtual ~ICommand() = default;

		virtual void execute(Context&) = 0;
	};

}}
