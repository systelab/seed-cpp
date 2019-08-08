#pragma once

#include "SeedCppCore/DAL/Translators/Db/IDatabaseEntityTranslator.h"

#include "TestUtilitiesInterface/EntityComparator.h"

#include "DbAdapterTestUtilities/Stubs/StubTableRecord.h"
#include "DbAdapterTestUtilities/Stubs/StubField.h"
#include "DbAdapterTestUtilities/Stubs/StubFieldValue.h"


using namespace testing;
using namespace systelab::test_utility;
using namespace systelab::db;
using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {
	
	template <typename _DatabaseTranslatorTestWrapper>
	class DatabaseTranslatorTest : public Test
	{
	public:
		void SetUp()
		{
			m_translator = _DatabaseTranslatorTestWrapper::buildDbTranslator(m_model);
		}

		std::unique_ptr<StubTableRecord> buildRecord(const std::vector<StubFieldValue>& data)
		{
			std::vector<std::unique_ptr<StubFieldValue> > fieldValues;
			for (auto cit = data.begin(); cit != data.end(); ++cit)
			{
				fieldValues.push_back(std::make_unique<StubFieldValue>(*cit));
			}

			return std::make_unique<StubTableRecord>(fieldValues);
		}

		std::unique_ptr<StubTableRecord> buildNullRecord(std::vector<StubFieldValue>& data)
		{
			std::vector<std::unique_ptr<StubFieldValue> > fieldValues;
			for (auto cit = data.begin(); cit != data.end(); cit++)
			{
				auto fieldValue = std::make_unique<StubFieldValue>(*cit);
				fieldValue->setNull();
				fieldValues.push_back(std::move(fieldValue));
			}

			return std::make_unique<StubTableRecord>(fieldValues);
		}

	protected:
		std::unique_ptr<dal::IDatabaseEntityTranslator> m_translator;
		typename _DatabaseTranslatorTestWrapper::ModelEntity m_model;
	};

	TYPED_TEST_CASE_P(DatabaseTranslatorTest);

	TYPED_TEST_P(DatabaseTranslatorTest, testFillEntityFromRecord)
	{
		std::vector<StubFieldValue> fieldValues = TypeParam::getRecordData();
		std::unique_ptr<StubTableRecord> record = this->buildRecord(fieldValues);

		this->m_translator->fillEntityFromRecord(*record);

		auto expectedModel = TypeParam::getEntity();
		ASSERT_TRUE(EntityComparator()(expectedModel, this->m_model));
	}

	TYPED_TEST_P(DatabaseTranslatorTest, testFillRecordFromEntity)
	{
		this->m_model = TypeParam::getEntity();

		std::vector<StubFieldValue> expectedFieldValues = TypeParam::getRecordData();
		std::unique_ptr<StubTableRecord> expectedRecord = this->buildRecord(expectedFieldValues);

		std::unique_ptr<StubTableRecord> recordToFill = this->buildNullRecord(expectedFieldValues);
		this->m_translator->fillRecordFromEntity(*recordToFill);

		ASSERT_TRUE(EntityComparator()((ITableRecord&) *expectedRecord, (ITableRecord&) *recordToFill));
	}

	REGISTER_TYPED_TEST_CASE_P(DatabaseTranslatorTest, testFillEntityFromRecord, testFillRecordFromEntity);
}}

