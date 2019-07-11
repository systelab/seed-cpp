#include "stdafx.h"
#include "SeedCppCore/Model/User.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const User& expected, const User& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getId());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getCreationTime());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getUpdateTime());

		COMPARATOR_ASSERT_EQUAL(expected, toTest, getSurname());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getName());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getLogin());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getPassword());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getRole());

		return AssertionSuccess();
	}

}}
