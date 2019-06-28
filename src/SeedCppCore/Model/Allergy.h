#pragma once

#include "SeedCppCore/Model/BaseEntity.h"


namespace seed_cpp { namespace model {

	class Allergy : public BaseEntity
	{
	public:
		Allergy();
		Allergy(const Allergy&);
		virtual ~Allergy();

		std::string getName() const;
		std::string getSigns() const;
		std::string getSymptoms() const;

		void setName(const std::string&);
		void setSigns(const std::string&);
		void setSymptoms(const std::string&);

		Allergy& operator=(const Allergy&);
		friend bool operator==(const Allergy&, const Allergy&);
		friend bool operator!=(const Allergy&, const Allergy&);

	private:
		std::string m_name;
		std::string m_signs;
		std::string m_symptoms;
	};

}}