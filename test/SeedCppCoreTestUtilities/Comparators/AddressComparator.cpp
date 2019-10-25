#include "stdafx.h"
#include "SeedCppCore/Model/Address.h"

#include "TestUtilitiesInterface/EntityComparator.h"
#include "TestUtilitiesInterface/EntityComparatorMacros.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const Address& expected, const Address& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getId());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getCoordinates());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getStreet());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getCity());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getZip());

		return AssertionSuccess();
	}

}}
