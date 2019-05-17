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
			const Patient* expectedPatient = expected.getEntity(i, expectedLock);
			if (!expectedPatient->getId())
			{
				return AssertionFailure() << "Patient " << i << " doesn't have identifer defined";
			}

			std::string patientId = *expectedPatient->getId();
			const Patient* toTestPatient = toTest.getEntityById(patientId, toTestLock);
			if (!toTestPatient)
			{
				return AssertionFailure() << "Patient with id=" << patientId << " not found in manager to test";
			}

			AssertionResult patientResult = EntityComparator()(*expectedPatient, *toTestPatient);
			if (!patientResult)
			{
				return AssertionFailure() << "Different data for patient with id=" << patientId << ": " << patientResult.message();
			}
		}

		return AssertionSuccess();
	}

}}
