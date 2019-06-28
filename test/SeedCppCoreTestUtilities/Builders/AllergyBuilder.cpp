#include "stdafx.h"
#include "AllergyBuilder.h"


namespace seed_cpp { namespace test_utility {

	AllergyBuilder::AllergyBuilder()
		:m_allergy()
	{
	}

	AllergyBuilder::~AllergyBuilder() = default;

	AllergyBuilder& AllergyBuilder::setId(const std::string& id)
	{
		m_allergy.setId(id);
		return *this;
	}

	AllergyBuilder& AllergyBuilder::setCreationTime(const boost::posix_time::ptime& creationTime)
	{
		m_allergy.setCreationTime(creationTime);
		return *this;
	}

	AllergyBuilder& AllergyBuilder::setUpdateTime(const boost::posix_time::ptime& updateTime)
	{
		m_allergy.setUpdateTime(updateTime);
		return *this;
	}

	AllergyBuilder& AllergyBuilder::setName(const std::string& name)
	{
		m_allergy.setName(name);
		return *this;
	}

	AllergyBuilder& AllergyBuilder::setSigns(const std::string& signs)
	{
		m_allergy.setSigns(signs);
		return *this;
	}

	AllergyBuilder& AllergyBuilder::setSymptoms(const std::string& symptoms)
	{
		m_allergy.setSymptoms(symptoms);
		return *this;
	}

	model::Allergy AllergyBuilder::getEntity() const
	{
		return m_allergy;
	}

}}
