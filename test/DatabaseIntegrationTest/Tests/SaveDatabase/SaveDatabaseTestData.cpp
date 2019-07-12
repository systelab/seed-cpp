#include "stdafx.h"
#include "SaveDatabaseTestData.h"


namespace seed_cpp { namespace db_test {

	SaveDatabaseTestData::SaveDatabaseTestData()
		:m_sqlScripts()
		,m_commands()
	{
	}

	SaveDatabaseTestData::SaveDatabaseTestData(const SaveDatabaseTestData& other)
		:m_sqlScripts(other.m_sqlScripts)
		,m_commands()
	{
		size_t nCommands = other.m_commands.size();
		for (size_t i = 0; i < nCommands; i++)
		{
			m_commands.push_back(other.m_commands[i]->clone());
		}
	}

	SaveDatabaseTestData::~SaveDatabaseTestData() = default;

	std::vector<std::string> SaveDatabaseTestData::getSQLScripts() const
	{
		return m_sqlScripts;
	}

	void SaveDatabaseTestData::setSQLScripts(const std::vector<std::string>& sqlScripts)
	{
		m_sqlScripts = sqlScripts;
	}

	size_t SaveDatabaseTestData::getCommandsCount() const
	{
		return m_commands.size();
	}

	ICommand& SaveDatabaseTestData::getCommand(unsigned int index) const
	{
		return *(m_commands[index]);
	}

	void SaveDatabaseTestData::addCommand(std::unique_ptr<ICommand> command)
	{
		m_commands.push_back(std::move(command));
	}

}}

