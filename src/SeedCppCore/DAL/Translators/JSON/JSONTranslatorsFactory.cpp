#include "stdafx.h"
#include "JSONTranslatorsFactory.h"

#include "DAL/Translators/JSON/AllergyJSONTranslator.h"
#include "DAL/Translators/JSON/PatientJSONTranslator.h"
#include "DAL/Translators/JSON/UserJSONTranslator.h"


namespace seed_cpp { namespace dal {

	JSONTranslatorsFactory::JSONTranslatorsFactory() = default;
	
	JSONTranslatorsFactory::~JSONTranslatorsFactory() = default;

	// Allergies
	std::unique_ptr<IJSONLoadTranslator> JSONTranslatorsFactory::buildAllergyLoadTranslator(model::Allergy& entity) const
	{
		return std::make_unique<dal::AllergyJSONLoadTranslator>(entity);
	}

	std::unique_ptr<IJSONSaveTranslator> JSONTranslatorsFactory::buildAllergySaveTranslator(const model::Allergy& entity) const
	{
		return std::make_unique<dal::AllergyJSONSaveTranslator>(entity);
	}

	// Patient
	std::unique_ptr<IJSONLoadTranslator> JSONTranslatorsFactory::buildPatientLoadTranslator(model::Patient& patient) const
	{
		return std::unique_ptr<IJSONLoadTranslator>(new dal::PatientJSONLoadTranslator(patient));
	}

	std::unique_ptr<IJSONSaveTranslator> JSONTranslatorsFactory::buildPatientSaveTranslator(const model::Patient& patient) const
	{
		return std::unique_ptr<IJSONSaveTranslator>(new dal::PatientJSONSaveTranslator(patient));
	}


	// User
	std::unique_ptr<IJSONLoadTranslator> JSONTranslatorsFactory::buildUserLoadTranslator(model::User& user) const
	{
		return std::unique_ptr<IJSONLoadTranslator>(new dal::UserJSONLoadTranslator(user));
	}

	std::unique_ptr<IJSONSaveTranslator> JSONTranslatorsFactory::buildUserSaveTranslator(const model::User& user) const
	{
		return std::unique_ptr<IJSONSaveTranslator>(new dal::UserJSONSaveTranslator(user));
	}

}}
