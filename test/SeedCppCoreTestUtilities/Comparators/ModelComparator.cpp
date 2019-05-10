#include "stdafx.h"
#include "SeedCppCore/Model/Model.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace seed_cpp::model;

namespace systelab { namespace test_utility {

	template<>
	AssertionResult EntityComparator::operator() (const Model& expected, const Model& toTest) const
	{
		AssertionResult userResult = EntityComparator()(expected.getUserMgr(), toTest.getUserMgr());
		if (!userResult)
		{
			return AssertionFailure() << userResult.message();
		}

		AssertionResult patientResult = EntityComparator()(expected.getPatientMgr(), toTest.getPatientMgr());
		if (!patientResult)
		{
			return AssertionFailure() << patientResult.message();
		}

		return AssertionSuccess();
	}

}}