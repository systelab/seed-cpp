#include "stdafx.h"
#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Model/UserMgr.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const UserMgr& expected, const UserMgr& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, count());

		UserMgr::SharedLock expectedLock(const_cast<UserMgr&>(expected));
		UserMgr::SharedLock toTestLock(const_cast<UserMgr&>(toTest));

		unsigned int nUsers = expected.count();
		for (unsigned int i = 0; i < nUsers; i++)
		{
			const User* expectedUser = expected.getEntity(i, expectedLock);
			if (!expectedUser->getId())
			{
				return AssertionFailure() << "User " << i << " doesn't have identifer defined";
			}

			std::string userId = *expectedUser->getId();
			const User* toTestUser = toTest.getEntityById(userId, toTestLock);
			if (!toTestUser)
			{
				return AssertionFailure() << "User with id=" << userId << " not found in manager to test";
			}

			AssertionResult userResult = EntityComparator()(*expectedUser, *toTestUser);
			if (!userResult)
			{
				return AssertionFailure() << "Different data for user with id=" << userId << ": " << userResult.message();
			}
		}

		return AssertionSuccess();
	}

}}
