#include "StdAfx.h"
#include "DbTranslatorsFactory.h"

#include "DAL/Translators/Db/AddressDbTranslator.h"
#include "DAL/Translators/Db/PatientDbTranslator.h"
#include "DAL/Translators/Db/UserDbTranslator.h"


namespace seed_cpp { namespace dal {

	DbTranslatorsFactory::DbTranslatorsFactory()
	{
	}
	
	DbTranslatorsFactory::~DbTranslatorsFactory()
	{
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildPatientTranslator(model::Patient& patient) const
	{
		return std::unique_ptr<IDatabaseEntityTranslator>(new dal::PatientDbTranslator(patient));
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildAddressTranslator(unsigned int patientId, model::Address& address) const
	{
		return std::unique_ptr<IDatabaseEntityTranslator>(new dal::AddressDbTranslator(patientId, address));
	}

	std::unique_ptr<IDatabaseEntityTranslator> DbTranslatorsFactory::buildUserTranslator(model::User& user) const
	{
		return std::unique_ptr<IDatabaseEntityTranslator>(new dal::UserDbTranslator(user));
	}

}}