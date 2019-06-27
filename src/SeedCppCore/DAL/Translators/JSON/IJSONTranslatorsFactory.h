#pragma once

#include <memory>


namespace seed_cpp { namespace model {
	class Address;
	class Allergy;
	class Patient;
	class User;
}}

namespace seed_cpp { namespace dal {

	class IJSONLoadTranslator;
	class IJSONSaveTranslator;

	class IJSONTranslatorsFactory
	{
	public:
		virtual ~IJSONTranslatorsFactory() = default;

		// Allergies
		virtual std::unique_ptr<IJSONLoadTranslator> buildAllergyLoadTranslator(model::Allergy&) const = 0;
		virtual std::unique_ptr<IJSONSaveTranslator> buildAllergySaveTranslator(const model::Allergy&) const = 0;

		// Patients
		virtual std::unique_ptr<IJSONLoadTranslator> buildPatientLoadTranslator(model::Patient&) const = 0;
		virtual std::unique_ptr<IJSONSaveTranslator> buildPatientSaveTranslator(const model::Patient&) const = 0;

		// Users
		virtual std::unique_ptr<IJSONLoadTranslator> buildUserLoadTranslator(model::User&) const = 0;
		virtual std::unique_ptr<IJSONSaveTranslator> buildUserSaveTranslator(const model::User&) const = 0;
	};

}}
