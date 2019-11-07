#include "stdafx.h"
#include "SeedCppCore/Model/Model.h"

#include "TestUtilitiesInterface/EntityComparator.h"
#include "TestUtilitiesInterface/EntityComparatorMacros.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const Model& expected, const Model& toTest) const
	{
		AssertionResult allergyResult = EntityComparator()(expected.getAllergyMgr(), toTest.getAllergyMgr());
		if (!allergyResult)
		{
			return AssertionFailure() << "Different data in allergy manager: " << allergyResult.message();
		}

		AssertionResult patientResult = EntityComparator()(expected.getPatientMgr(), toTest.getPatientMgr());
		if (!patientResult)
		{
			return AssertionFailure() << "Different data in patient manager: " << patientResult.message();
		}

		AssertionResult userResult = EntityComparator()(expected.getUserMgr(), toTest.getUserMgr());
		if (!userResult)
		{
			return AssertionFailure() << "Different data in user manager: " << userResult.message();
		}

		return AssertionSuccess();
	}

}}
