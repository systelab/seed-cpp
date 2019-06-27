#include "stdafx.h"
#include "SeedCppCore/Model/Allergy.h"


namespace seed_cpp { namespace test_utility {

	class AllergyBuilder
	{
	public:
		AllergyBuilder();
		virtual ~AllergyBuilder();

		AllergyBuilder& setId(const std::string&);
		AllergyBuilder& setCreationTime(const boost::posix_time::ptime&);
		AllergyBuilder& setUpdateTime(const boost::posix_time::ptime&);
		AllergyBuilder& setName(const std::string&);
		AllergyBuilder& setSigns(const std::string&);
		AllergyBuilder& setSymptoms(const std::string&);

		model::Allergy getEntity() const;

	private:
		model::Allergy m_allergy;
	};

}}
