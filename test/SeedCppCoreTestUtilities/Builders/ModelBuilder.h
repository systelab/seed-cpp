#include "stdafx.h"

#include "SeedCppCore/Model/Model.h"


namespace seed_cpp { namespace test_utility {

	class ModelBuilder
	{
	public:
		ModelBuilder();
		virtual ~ModelBuilder();

		ModelBuilder& setUsers(const std::vector<model::User>&);
		ModelBuilder& setPatients(const std::vector<model::Patient>&);

		model::Model getEntity() const;

	private:
		model::Model m_model;
	};

}}
