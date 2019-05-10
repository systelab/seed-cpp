#pragma once

#include "SeedCppCore/Core.h"


namespace seed_cpp { namespace db_test {

	class Context : public Core
	{
	public:
		Context(const std::string&);
		virtual ~Context();

		void initialize();

	protected:
		void initializeDatabase();

	private:
		std::string m_databaseFilepath;
	};

}}