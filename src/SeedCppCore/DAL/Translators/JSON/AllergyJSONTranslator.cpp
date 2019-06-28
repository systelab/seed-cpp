#include "stdafx.h"
#include "AllergyJSONTranslator.h"

#include "Model/Allergy.h"


namespace seed_cpp { namespace dal {

	// Save translator
	AllergyJSONSaveTranslator::AllergyJSONSaveTranslator(const model::Allergy& entity)
		:m_entity(entity)
	{
	}

	AllergyJSONSaveTranslator::~AllergyJSONSaveTranslator() = default;

	void AllergyJSONSaveTranslator::saveEntityToJSON(systelab::json::IJSONValue& jsonEntity) const
	{
		jsonEntity.setType(systelab::json::OBJECT_TYPE);
		jsonEntity.addMember("id", *m_entity.getId());
		jsonEntity.addMember("name", m_entity.getName());
		jsonEntity.addMember("signs", m_entity.getSigns());
		jsonEntity.addMember("symptoms", m_entity.getSymptoms());
	}

	// Load translator
	AllergyJSONLoadTranslator::AllergyJSONLoadTranslator(model::Allergy& entity)
		:m_entity(entity)
	{
	}

	AllergyJSONLoadTranslator::~AllergyJSONLoadTranslator() = default;

	void AllergyJSONLoadTranslator::loadEntityFromJSON(const systelab::json::IJSONValue& jsonEntity)
	{
		if (jsonEntity.hasObjectMember("name"))
		{
			std::string name = jsonEntity.getObjectMemberValue("name").getString();
			m_entity.setName(name);
		}

		if (jsonEntity.hasObjectMember("signs"))
		{
			std::string signs = jsonEntity.getObjectMemberValue("signs").getString();
			m_entity.setSigns(signs);
		}

		if (jsonEntity.hasObjectMember("symptoms"))
		{
			std::string symptoms = jsonEntity.getObjectMemberValue("symptoms").getString();
			m_entity.setSymptoms(symptoms);
		}
	}

}}
