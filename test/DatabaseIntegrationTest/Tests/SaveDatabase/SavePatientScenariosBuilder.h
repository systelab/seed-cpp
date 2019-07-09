#pragma once

#include "Tests/SaveDatabase/SaveDatabaseTestData.h"


namespace seed_cpp { namespace db_test {

	class SavePatientScenariosBuilder
	{
	public:
		static std::vector<SaveDatabaseTestData> build();
	};

}}

