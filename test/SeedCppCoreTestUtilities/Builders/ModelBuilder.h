#include "stdafx.h"

#include "SeedCppCore/Model/Allergy.h"
#include "SeedCppCore/Model/Model.h"
#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace test_utility {

	class ModelBuilder
	{
	public:
		ModelBuilder();
		virtual ~ModelBuilder();

		ModelBuilder& setAllergies(const std::vector<model::Allergy>&);
		ModelBuilder& setPatients(const std::vector<model::Patient>&);
		ModelBuilder& setUsers(const std::vector<model::User>&);

		model::Model getEntity() const;

	private:
		model::Model m_model;
	};

}}
