#include "stdafx.h"
#include "SeedCppCore/REST/Helpers/ReplyBuilderHelper.h"


using namespace testing;

namespace seed_cpp { namespace unit_test {

	namespace {
		struct ReplyBuilderHelperTestData
		{
			systelab::web_server::Reply::StatusType status;
			std::string content;
			std::string expectedContentLength;
		};

		std::vector<ReplyBuilderHelperTestData> testData =
		{
			{ systelab::web_server::Reply::OK,			"{}",					"2"  },
			{ systelab::web_server::Reply::CREATED,		"{\"data\": 3}",		"11" },
			{ systelab::web_server::Reply::FORBIDDEN,	"{\"data\": false}",	"15" },
			{ systelab::web_server::Reply::NOT_FOUND,	"[]",					"2"  },
			{ systelab::web_server::Reply::BAD_REQUEST,	"{\"data\": []}",		"12" },
		};
	}

	class ReplyBuilderHelperTest : public TestWithParam<ReplyBuilderHelperTestData>
	{
		void SetUp()
		{
			m_helper = std::make_unique<rest::ReplyBuilderHelper>();
		}

	protected:
		std::unique_ptr<rest::ReplyBuilderHelper> m_helper;
	};

	TEST_P(ReplyBuilderHelperTest, testBuild)
	{
		auto reply = m_helper->build(GetParam().status, GetParam().content);

		ASSERT_TRUE(reply != nullptr);
		EXPECT_EQ(GetParam().status, reply->getStatus());
		EXPECT_EQ(GetParam().content, reply->getContent());
		EXPECT_EQ(2u, reply->getHeaders().size());

		ASSERT_TRUE(reply->hasHeader("Content-Type"));
		EXPECT_EQ("application/json", reply->getHeader("Content-Type"));

		ASSERT_TRUE(reply->hasHeader("Content-Length"));
		EXPECT_EQ(GetParam().expectedContentLength, reply->getHeader("Content-Length"));
	}

	INSTANTIATE_TEST_CASE_P(Helpers, ReplyBuilderHelperTest, testing::ValuesIn(testData));

}}

