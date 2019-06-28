#include "stdafx.h"
#include "DbTranslatorsFactory.h"

#include "DAL/Translators/Db/AddressDbTranslator.h"
#include "DAL/Translators/Db/AllergyDbTranslator.h"
#include "DAL/Translators/Db/PatientDbTranslator.h"
#include "DAL/Translators/Db/UserDbTranslator.h"


namespace seed_cpp { namespace dal {

	DbTranslatorsFactory::DbTranslatorsFactory()
	{
	}
	
	DbTranslatorsFactory::~DbTranslatorsFactory() = default;

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildAddressTranslator(const std::string& patientId, model::Address& address) const
	{
		return std::make_unique<AddressDbTranslator>(patientId, address);
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildAllergyTranslator(model::Allergy& allergy) const
	{
		return std::make_unique<AllergyDbTranslator>(allergy);
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildPatientTranslator(model::Patient& patient) const
	{
		return std::make_unique<PatientDbTranslator>(patient);
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildUserTranslator(model::User& user) const
	{
		return std::make_unique<UserDbTranslator>(user);
	}

}}
