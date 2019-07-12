#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace db_test {

	class SaveDatabaseTestData
	{
	public:
		SaveDatabaseTestData();
		SaveDatabaseTestData(const SaveDatabaseTestData&);
		virtual ~SaveDatabaseTestData();

		std::vector<std::string> getSQLScripts() const;
		void setSQLScripts(const std::vector<std::string>&);

		size_t getCommandsCount() const;
		ICommand& getCommand(unsigned int index) const;
		void addCommand(std::unique_ptr<ICommand>);

	private:
		std::vector<std::string> m_sqlScripts;
		std::vector< std::unique_ptr<ICommand> > m_commands;
	};

}}

