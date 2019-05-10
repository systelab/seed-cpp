#include "stdafx.h"
#include "SeedCppCore/Model/EntityMgr.h"
#include "SeedCppCore/Model/User.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const EntityMgr<User>& expected, const EntityMgr<User>& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, count());

		EntityMgr<User>::SharedLock expectedLock(const_cast<EntityMgr<User>&>(expected));
		EntityMgr<User>::SharedLock toTestLock(const_cast<EntityMgr<User>&>(toTest));

		unsigned int nUsers = expected.count();
		for (unsigned int i = 0; i < nUsers; i++)
		{
			AssertionResult userResult = EntityComparator()(*expected.getEntity(i, expectedLock), *toTest.getEntity(i, toTestLock));
			if (!userResult)
			{
				return AssertionFailure() << "Different data for user " << i << ": " << userResult.message();
			}
		}

		return AssertionSuccess();
	}

}}
