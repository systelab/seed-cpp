#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONTranslatorsFactory.h"

#include "SeedCppCore/DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "SeedCppCore/DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace test_utility {

	class MockJSONTranslatorsFactory : public dal::IJSONTranslatorsFactory
	{
	public:
		MockJSONTranslatorsFactory();
		virtual ~MockJSONTranslatorsFactory();

		// Allergies
		MOCK_CONST_METHOD1(buildAllergyLoadTranslatorProxy, dal::IJSONLoadTranslator*(model::Allergy&));
		std::unique_ptr<dal::IJSONLoadTranslator> buildAllergyLoadTranslator(model::Allergy& allergy) const override
		{
			return std::unique_ptr<dal::IJSONLoadTranslator>(buildAllergyLoadTranslatorProxy(allergy));
		}

		MOCK_CONST_METHOD1(buildAllergySaveTranslatorProxy, dal::IJSONSaveTranslator*(const model::Allergy&));
		std::unique_ptr<dal::IJSONSaveTranslator> buildAllergySaveTranslator(const model::Allergy& allergy) const override
		{
			return std::unique_ptr<dal::IJSONSaveTranslator>(buildAllergySaveTranslatorProxy(allergy));
		}


		// Patients
		MOCK_CONST_METHOD1(buildPatientLoadTranslatorProxy, dal::IJSONLoadTranslator*(model::Patient&));
		std::unique_ptr<dal::IJSONLoadTranslator> buildPatientLoadTranslator(model::Patient& patient) const override
		{
			return std::unique_ptr<dal::IJSONLoadTranslator>(buildPatientLoadTranslatorProxy(patient));
		}

		MOCK_CONST_METHOD1(buildPatientSaveTranslatorProxy, dal::IJSONSaveTranslator*(const model::Patient&));
		std::unique_ptr<dal::IJSONSaveTranslator> buildPatientSaveTranslator(const model::Patient& patient) const override
		{
			return std::unique_ptr<dal::IJSONSaveTranslator>(buildPatientSaveTranslatorProxy(patient));
		}


		// Users
		MOCK_CONST_METHOD1(buildUserLoadTranslatorProxy, dal::IJSONLoadTranslator*(model::User&));
		std::unique_ptr<dal::IJSONLoadTranslator> buildUserLoadTranslator(model::User& user) const override
		{
			return std::unique_ptr<dal::IJSONLoadTranslator>(buildUserLoadTranslatorProxy(user));
		}

		MOCK_CONST_METHOD1(buildUserSaveTranslatorProxy, dal::IJSONSaveTranslator*(const model::User&));
		std::unique_ptr<dal::IJSONSaveTranslator> buildUserSaveTranslator(const model::User& user) const override
		{
			return std::unique_ptr<dal::IJSONSaveTranslator>(buildUserSaveTranslatorProxy(user));
		}
	};

}}
