#pragma once

#include "IJSONSaveTranslator.h"
#include "IJSONLoadTranslator.h"


namespace seed_cpp { namespace model {
	class Allergy;
}}

namespace seed_cpp { namespace dal {

	class AllergyJSONSaveTranslator : public IJSONSaveTranslator
	{
	public:
		AllergyJSONSaveTranslator(const model::Allergy&);
		virtual ~AllergyJSONSaveTranslator();

		void saveEntityToJSON(systelab::json::IJSONValue&) const override;

	private:
		const model::Allergy& m_entity;
	};


	class AllergyJSONLoadTranslator : public IJSONLoadTranslator
	{
	public:
		AllergyJSONLoadTranslator(model::Allergy&);
		virtual ~AllergyJSONLoadTranslator();

		void loadEntityFromJSON(const systelab::json::IJSONValue&) override;

	protected:
		model::Allergy& m_entity;
	};

}}