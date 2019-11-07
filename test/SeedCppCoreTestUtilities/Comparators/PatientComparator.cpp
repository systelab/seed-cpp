#include "stdafx.h"
#include "SeedCppCore/Model/Patient.h"

#include "TestUtilitiesInterface/EntityComparator.h"
#include "TestUtilitiesInterface/EntityComparatorMacros.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const Patient& expected, const Patient& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getId());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getCreationTime());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getUpdateTime());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getSurname());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getName());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getEmail());
		COMPARATOR_ASSERT_EQUAL(expected, toTest, getDob());

		auto& expectedAddress = expected.getAddress();
		auto& toTestAddress = toTest.getAddress();
		AssertionResult addressResult = EntityComparator()(expectedAddress, toTestAddress);
		if (!addressResult)
		{
			return AssertionFailure() << "Different address data: " << addressResult.message();
		}

		return AssertionSuccess();
	}

}}
