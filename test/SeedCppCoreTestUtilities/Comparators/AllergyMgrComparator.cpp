#include "stdafx.h"
#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/AllergyMgr.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const AllergyMgr& expected, const AllergyMgr& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, count());

		AllergyMgr::SharedLock expectedLock(const_cast<AllergyMgr&>(expected));
		AllergyMgr::SharedLock toTestLock(const_cast<AllergyMgr&>(toTest));

		unsigned int nAllergies = expected.count();
		for (unsigned int i = 0; i < nAllergies; i++)
		{
			const Allergy* expectedAllergy = expected.getEntity(i, expectedLock);
			if (!expectedAllergy->getId())
			{
				return AssertionFailure() << "Allergy " << i << " doesn't have identifer defined";
			}

			std::string allergyId = *expectedAllergy->getId();
			const Allergy* toTestAllergy = toTest.getEntityById(allergyId, toTestLock);
			if (!toTestAllergy)
			{
				return AssertionFailure() << "Allergy with id=" << allergyId << " not found in manager to test";
			}

			AssertionResult allergyResult = EntityComparator()(*expectedAllergy, *toTestAllergy);
			if (!allergyResult)
			{
				return AssertionFailure() << "Different data for allergy with id=" << allergyId << ": " << allergyResult.message();
			}
		}

		return AssertionSuccess();
	}

}}
