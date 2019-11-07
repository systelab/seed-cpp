#include "stdafx.h"
#include "SeedCppCore/REST/Helpers/RequestURLEncodedParserHelper.h"


using namespace testing;

namespace seed_cpp { namespace unit_test {

	namespace {
		struct RequestURLEncodedParserHelperTestData
		{
			std::string requestContent;
			std::map<std::string, std::string> expectedParameters;
		};

		std::vector<RequestURLEncodedParserHelperTestData> testData =
		{
			{ "",									{} },
			{ "Param1",								{} },
			{ "Param1=",							{} },
			{ "=Value1",							{} },
			{ "Param1=Value1=Value2",				{} },
			{ "Param1=Value1",						{ {"Param1", "Value1"} } },
			{ "Param1=Value1&Param2",				{ {"Param1", "Value1"} } },
			{ "Param1=Value1&Param2=Value2",		{ {"Param1", "Value1"}, {"Param2", "Value2"} } },
		};
	}

	class RequestURLEncodedParserHelperTest : public TestWithParam<RequestURLEncodedParserHelperTestData>
	{
		void SetUp()
		{
			m_helper = std::make_unique<rest::RequestURLEncodedParserHelper>();
		}

	protected:
		std::unique_ptr<rest::RequestURLEncodedParserHelper> m_helper;
	};

	TEST_P(RequestURLEncodedParserHelperTest, testParse)
	{
		auto parameters = m_helper->parse(GetParam().requestContent);
		ASSERT_EQ(GetParam().expectedParameters.size(), parameters.size());
		
		for (auto it = parameters.begin(); it != parameters.end(); it++)
		{
			std::string parameterName = it->first;
			auto findIt = GetParam().expectedParameters.find(parameterName);
			ASSERT_TRUE(findIt != GetParam().expectedParameters.end()) << "Parameter name='" << parameterName << "'";

			std::string parameterValue = it->second;
			ASSERT_EQ(parameterValue, findIt->second) << "Parameter name='" << parameterName << "'";
		}
	}

	INSTANTIATE_TEST_CASE_P(Helpers, RequestURLEncodedParserHelperTest, testing::ValuesIn(testData));

}}

