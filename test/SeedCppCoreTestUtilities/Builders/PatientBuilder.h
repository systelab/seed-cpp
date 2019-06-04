#include "stdafx.h"
#include "SeedCppCore/Model/Patient.h"


namespace seed_cpp { namespace test_utility {

	class PatientBuilder
	{
	public:
		PatientBuilder();
		virtual ~PatientBuilder();

		PatientBuilder& setId(const std::string&);
		PatientBuilder& setCreationTime(const boost::posix_time::ptime&);
		PatientBuilder& setUpdateTime(const boost::posix_time::ptime&);
		PatientBuilder& setSurname(const std::string&);
		PatientBuilder& setName(const std::string&);
		PatientBuilder& setEmail(const std::string&);
		PatientBuilder& setDob(const boost::posix_time::ptime&);
		PatientBuilder& setAddress(std::unique_ptr<model::Address>);

		model::Patient getEntity() const;

	private:
		model::Patient m_patient;
	};

}}
