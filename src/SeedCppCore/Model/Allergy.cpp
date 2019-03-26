#include "stdafx.h"
#include "Allergy.h"

namespace seed_cpp { namespace model {

	Allergy::Allergy()
		:m_name("")
		,m_signs("")
		,m_symptoms("")
	{
	}

	Allergy::Allergy(const Allergy& other)
		:m_name(other.m_name)
		,m_signs(other.m_signs)
		,m_symptoms(other.m_symptoms)
	{
	}

	Allergy::~Allergy() = default;

	std::string Allergy::getName()
	{
		return m_name;
	}

	std::string Allergy::getSigns()
	{
		return m_signs;
	}

	std::string Allergy::getSymptoms()
	{
		return m_symptoms;
	}

	void Allergy::setName(const std::string& name)
	{
		m_name = name;
	}

	void Allergy::setSigns(const std::string& signs)
	{
		m_signs = signs;
	}

	void Allergy::setSymptoms(const std::string& symptoms)
	{
		m_symptoms = symptoms;
	}

	Allergy& Allergy::operator=(const Allergy& other)
	{
		BaseEntity::operator=(other);

		m_name		= other.m_name;
		m_signs		= other.m_signs;
		m_symptoms	= other.m_symptoms;
		
		return *this;
	}

	bool operator==(const Allergy& lhs, const Allergy& rhs)
	{
		const auto& lhsBase = static_cast<const BaseEntity&>(lhs);
		const auto& rhsBase = static_cast<const BaseEntity&>(rhs);
		if (lhsBase != rhsBase)
		{
			return false;
		}

		if (lhs.m_name != rhs.m_name
			|| lhs.m_signs != rhs.m_signs
			|| lhs.m_symptoms != rhs.m_symptoms)
		{
			return false;
		}

		return true;
	}

	bool operator!=(const Allergy& lhs, const Allergy& rhs)
	{
		return !(lhs == rhs);
	}

}}