#pragma once

#include "SeedCppCore/Model/Model.h"
#include "TestUtilitiesInterface/EntityComparatorConfiguration.h"


namespace seed_cpp { namespace db_test {

	struct LoadEntityTestData
	{
		std::string m_sqlFilename;
		model::Model m_expectedModel;
		systelab::test_utility::EntityComparatorConfiguration m_comparatorConfig;
	};

}}
