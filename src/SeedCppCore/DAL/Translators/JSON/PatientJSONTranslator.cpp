#include "StdAfx.h"
#include "PatientJSONTranslator.h"

#include "Model/Address.h"
#include "Model/Patient.h"


namespace seed_cpp { namespace dal {

	PatientJSONSaveTranslator::PatientJSONSaveTranslator(const model::Patient& patient)
		:m_patient(patient)
	{
	}

	PatientJSONSaveTranslator::~PatientJSONSaveTranslator()
	{
	}

	void PatientJSONSaveTranslator::saveEntityToJSON(systelab::json_adapter::IJSONValue& jsonPatient,
													 systelab::json_adapter::IJSONDocument& jsonDocument) const
	{
		//jsonPatient.addMember("id", *m_patient.getId());
	}


	PatientJSONLoadTranslator::PatientJSONLoadTranslator(model::Patient& patient)
		:m_patient(patient)
	{
	}

	PatientJSONLoadTranslator::~PatientJSONLoadTranslator()
	{
	}

	void PatientJSONLoadTranslator::loadEntityFromJSON(const systelab::json_adapter::IJSONValue& jsonPatient)
	{
		if (jsonPatient.hasObjectMember("name"))
		{
			std::string name = jsonPatient.getObjectMemberValue("name").getString();
			m_patient.setName(name);
		}

		if (jsonPatient.hasObjectMember("surname"))
		{
			std::string surname = jsonPatient.getObjectMemberValue("surname").getString();
			m_patient.setSurname(surname);
		}
	}

}}
