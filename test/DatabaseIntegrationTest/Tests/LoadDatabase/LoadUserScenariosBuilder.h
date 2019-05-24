#pragma once

#include "Tests/LoadDatabase/LoadDatabaseTestData.h"


namespace seed_cpp { namespace db_test {

	class LoadUserScenariosBuilder
	{
	public:
		static std::vector<LoadDatabaseTestData> build();
	};

}}
