#include "stdafx.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const PatientMgr& expected, const PatientMgr& toTest) const
	{
		COMPARATOR_ASSERT_EQUAL(expected, toTest, count());

		PatientMgr::SharedLock expectedLock(const_cast<PatientMgr&>(expected));
		PatientMgr::SharedLock toTestLock(const_cast<PatientMgr&>(toTest));

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
