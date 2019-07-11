#pragma once


namespace seed_cpp { namespace db_test {

	class Core;

	class ICommand
	{
	public:
		virtual ~ICommand() = default;

		virtual void execute(Core&) = 0;
		virtual std::unique_ptr<ICommand> clone() = 0;
	};

}}
