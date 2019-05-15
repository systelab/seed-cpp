#pragma once

#include "Commands/ModelCommand.h"

namespace snow { namespace user { namespace dbtest {
	class ModifyDatabaseData
	{
	public:
		ModifyDatabaseData(const std::string& initialDBFilename, std::vector<ModelCommand*> commands);

		std::string m_initialDBFilename;
		std::vector<ModelCommand* > m_commands;
	};
}}}
