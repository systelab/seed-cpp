#include "stdafx.h"
#include "SeedCppCore/Model/EntityMgr.h"
#include "SeedCppCore/Model/Patient.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const EntityMgr<Patient>& expected, const EntityMgr<Patient>& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, count());

		EntityMgr<Patient>::SharedLock expectedLock(const_cast<EntityMgr<Patient>&>(expected));
		EntityMgr<Patient>::SharedLock toTestLock(const_cast<EntityMgr<Patient>&>(toTest));

		unsigned int nPatients = expected.count();
		for (unsigned int i = 0; i < nPatients; i++)
		{
			AssertionResult patientResult = EntityComparator()(*expected.getEntity(i, expectedLock), *toTest.getEntity(i, toTestLock));
			if (!patientResult)
			{
				return AssertionFailure() << "Different data for patient " << i << ": " << patientResult.message();
			}
		}

		return AssertionSuccess();
	}

}}
