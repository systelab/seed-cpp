#pragma once

#include "IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace dal {

	class JSONTranslatorsFactory : public IJSONTranslatorsFactory
	{
	public:
		JSONTranslatorsFactory();
		virtual ~JSONTranslatorsFactory();

		// Allergies
		std::unique_ptr<IJSONLoadTranslator> buildAllergyLoadTranslator(model::Allergy&) const override;
		std::unique_ptr<IJSONSaveTranslator> buildAllergySaveTranslator(const model::Allergy&) const override;

		// Patients
		std::unique_ptr<IJSONLoadTranslator> buildPatientLoadTranslator(model::Patient&) const override;
		std::unique_ptr<IJSONSaveTranslator> buildPatientSaveTranslator(const model::Patient&) const override;

		// Users
		std::unique_ptr<IJSONLoadTranslator> buildUserLoadTranslator(model::User&) const override;
		std::unique_ptr<IJSONSaveTranslator> buildUserSaveTranslator(const model::User&) const override;
	};

}}

