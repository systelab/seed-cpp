#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "SeedCppCore/DAL/Translators/JSON/IJSONLoadTranslator.h"

#include "RapidJSONAdapter/JSONAdapter.h"

#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"

#include "TestUtilitiesInterface/EntityComparator.h"


using namespace testing;
using namespace systelab::test_utility;

namespace seed_cpp { namespace unit_test {

	/**
	 * This tests checks that this translator is able to generate a JSON from a model entity and viceversa.
	 */
	
	// Class to test the IJSONLoadTranslator::loadEntityFromJSON() method
	template <typename _JSONTranslatorTestWrapper>
	class JSONTranslatorLoadTest : public Test
	{
	public:
		void SetUp()
		{
			m_translator = _JSONTranslatorTestWrapper::buildJSONLoadTranslator(m_model);
		}

		void TearDown()
		{
			_JSONTranslatorTestWrapper::tearDownWrapper();
		}

	protected:
		std::unique_ptr<dal::IJSONLoadTranslator> m_translator;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
		typename _JSONTranslatorTestWrapper::ModelEntity m_model;
	};

	TYPED_TEST_CASE_P(JSONTranslatorLoadTest);

	TYPED_TEST_P(JSONTranslatorLoadTest, testLoadEntityFromJSON)
	{
		auto document = m_jsonAdapter.buildDocumentFromString(TypeParam::getJSONString());
		ASSERT_TRUE(document != NULL);

		m_translator->loadEntityFromJSON(*document);

		auto expectedModel = TypeParam::getEntity();
		ASSERT_TRUE(EntityComparator()(expectedModel, m_model));
	}

	REGISTER_TYPED_TEST_CASE_P(JSONTranslatorLoadTest, testLoadEntityFromJSON);


	// Class to test the IJSONSaveTranslator::saveEntityToJSON() method
	template <typename _JSONTranslatorTestWrapper>
	class JSONTranslatorSaveTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_translator = _JSONTranslatorTestWrapper::buildJSONSaveTranslator(m_model);
		}

		void TearDown()
		{
			_JSONTranslatorTestWrapper::tearDownWrapper();
		}

	protected:
		std::unique_ptr<dal::IJSONSaveTranslator> m_translator;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
		typename _JSONTranslatorTestWrapper::ModelEntity m_model;
	};

	TYPED_TEST_CASE_P(JSONTranslatorSaveTest);

	TYPED_TEST_P(JSONTranslatorSaveTest, testSaveEntityToJSON)
	{
		m_model = TypeParam::getEntity();

		auto document = m_jsonAdapter.buildEmptyDocument();
		document->getRootValue().setType(systelab::json::OBJECT_TYPE);
		m_translator->saveEntityToJSON(document->getRootValue());

		auto expectedDocument = m_jsonAdapter.buildDocumentFromString(TypeParam::getJSONString());
		ASSERT_TRUE(expectedDocument != NULL);
		ASSERT_TRUE(EntityComparator()(*expectedDocument, *document));
	}

	REGISTER_TYPED_TEST_CASE_P(JSONTranslatorSaveTest, testSaveEntityToJSON);


	// Default wrapper class for all tests
	struct JSONTranslatorTestWrapper
	{
		static void tearDownWrapper()
		{
		}
	};

}}
