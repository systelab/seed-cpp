#include "stdafx.h"
#include "SeedCppCore/Model/Allergy.h"

#include "TestUtilitiesInterface/EntityComparator.h"
#include "TestUtilitiesInterface/EntityComparatorMacros.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const Allergy& expected, const Allergy& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getId());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getCreationTime());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getUpdateTime());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getName());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getSigns());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getSymptoms());

		return AssertionSuccess();
	}

}}
