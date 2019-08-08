#include "stdafx.h"
#include "PatientJSONTranslator.h"

#include "Model/Address.h"
#include "Model/Patient.h"


namespace seed_cpp { namespace dal {

	PatientJSONSaveTranslator::PatientJSONSaveTranslator(const model::Patient& patient)
		:m_patient(patient)
	{
	}

	PatientJSONSaveTranslator::~PatientJSONSaveTranslator() = default;

	void PatientJSONSaveTranslator::saveEntityToJSON(systelab::json::IJSONValue& jsonPatient) const
	{
		jsonPatient.setType(systelab::json::OBJECT_TYPE);
		jsonPatient.addMember("id", *m_patient.getId());
		jsonPatient.addMember("surname", m_patient.getSurname());
		jsonPatient.addMember("name", m_patient.getName());
		jsonPatient.addMember("email", m_patient.getEmail());

		auto dob = m_patient.getDob();
		if (dob)
		{
			jsonPatient.addMember("dob", boost::posix_time::to_iso_extended_string(*m_patient.getDob()));
		}

		model::Address& address = m_patient.getAddress();
		std::unique_ptr<systelab::json::IJSONValue> jsonAddress = jsonPatient.buildValue(systelab::json::OBJECT_TYPE);
		jsonAddress->addMember("coordinates", address.getCoordinates());
		jsonAddress->addMember("street", address.getStreet());
		jsonAddress->addMember("city", address.getCity());
		jsonAddress->addMember("zip", address.getZip());
		jsonPatient.addMember("address", std::move(jsonAddress));
	}


	PatientJSONLoadTranslator::PatientJSONLoadTranslator(model::Patient& patient)
		:m_patient(patient)
	{
	}

	PatientJSONLoadTranslator::~PatientJSONLoadTranslator() = default;

	void PatientJSONLoadTranslator::loadEntityFromJSON(const systelab::json::IJSONValue& jsonPatient)
	{
		if (jsonPatient.hasObjectMember("surname"))
		{
			std::string surname = jsonPatient.getObjectMemberValue("surname").getString();
			m_patient.setSurname(surname);
		}

		if (jsonPatient.hasObjectMember("name"))
		{
			std::string name = jsonPatient.getObjectMemberValue("name").getString();
			m_patient.setName(name);
		}

		if (jsonPatient.hasObjectMember("email"))
		{
			std::string email = jsonPatient.getObjectMemberValue("email").getString();
			m_patient.setEmail(email);
		}

		if (jsonPatient.hasObjectMember("dob"))
		{
			boost::posix_time::ptime dob = boost::posix_time::from_iso_extended_string(jsonPatient.getObjectMemberValue("dob").getString());
			m_patient.setDob(dob);
		}

		if (jsonPatient.hasObjectMember("address"))
		{
			const systelab::json::IJSONValue& jsonAddress = jsonPatient.getObjectMemberValue("address");
			std::string coordinates = jsonAddress.getObjectMemberValue("coordinates").getString();
			std::string street = jsonAddress.getObjectMemberValue("street").getString();
			std::string city = jsonAddress.getObjectMemberValue("city").getString();
			std::string zip = jsonAddress.getObjectMemberValue("zip").getString();

			model::Address& address = m_patient.getAddress();
			address.setCoordinates(coordinates);
			address.setStreet(street);
			address.setCity(city);
			address.setZip(zip);
		}
	}

}}
