#include "stdafx.h"
#include "PatientBuilder.h"


namespace seed_cpp { namespace test_utility {

	PatientBuilder::PatientBuilder()
		:m_patient()
	{
	}

	PatientBuilder::~PatientBuilder() = default;

	PatientBuilder& PatientBuilder::setId(const std::string& id)
	{
		m_patient.setId(id);
		return *this;
	}

	PatientBuilder& PatientBuilder::setCreationTime(const boost::posix_time::ptime& creationTime)
	{
		m_patient.setCreationTime(creationTime);
		return *this;
	}

	PatientBuilder& PatientBuilder::setUpdateTime(const boost::posix_time::ptime& updateTime)
	{
		m_patient.setUpdateTime(updateTime);
		return *this;
	}

	PatientBuilder& PatientBuilder::setSurname(const std::string& surname)
	{
		m_patient.setSurname(surname);
		return *this;
	}

	PatientBuilder& PatientBuilder::setName(const std::string& name)
	{
		m_patient.setName(name);
		return *this;
	}

	PatientBuilder& PatientBuilder::setEmail(const std::string& email)
	{
		m_patient.setEmail(email);
		return *this;
	}

	PatientBuilder& PatientBuilder::setDob(const boost::posix_time::ptime& dob)
	{
		m_patient.setDob(dob);
		return *this;
	}

	PatientBuilder& PatientBuilder::setAddress(std::unique_ptr<model::Address> address)
	{
		m_patient.setAddress(std::move(address));
		return *this;
	}

	model::Patient PatientBuilder::getEntity() const
	{
		return m_patient;
	}

}}
