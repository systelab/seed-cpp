#pragma once

#include "Tests/SaveDatabase/SaveDatabaseTestData.h"


namespace seed_cpp { namespace db_test {

	class SaveUserScenariosBuilder
	{
	public:
		static std::vector<SaveDatabaseTestData> build();
	};

}}

