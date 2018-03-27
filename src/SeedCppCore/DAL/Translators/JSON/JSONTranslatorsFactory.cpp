#include "StdAfx.h"
#include "JSONTranslatorsFactory.h"

#include "DAL/Translators/JSON/PatientJSONTranslator.h"


namespace seed_cpp { namespace dal {

	JSONTranslatorsFactory::JSONTranslatorsFactory()
	{
	}
	
	JSONTranslatorsFactory::~JSONTranslatorsFactory()
	{
	}

	std::unique_ptr<IJSONLoadTranslator> JSONTranslatorsFactory::buildPatientLoadTranslator(model::Patient& patient) const
	{
		return std::unique_ptr<IJSONLoadTranslator>(new dal::PatientJSONLoadTranslator(patient));
	}

	std::unique_ptr<IJSONSaveTranslator> JSONTranslatorsFactory::buildPatientSaveTranslator(const model::Patient& patient) const
	{
		return std::unique_ptr<IJSONSaveTranslator>(new dal::PatientJSONSaveTranslator(patient));
	}

}}
