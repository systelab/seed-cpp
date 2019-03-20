#pragma once

#include "IJSONSaveTranslator.h"
#include "IJSONLoadTranslator.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class PatientJSONSaveTranslator : public IJSONSaveTranslator
	{
	public:
		PatientJSONSaveTranslator(const model::Patient&);
		virtual ~PatientJSONSaveTranslator();

		void saveEntityToJSON(systelab::json::IJSONValue&) const;

	private:
		const model::Patient& m_patient;
	};


	class PatientJSONLoadTranslator : public IJSONLoadTranslator
	{
	public:
		PatientJSONLoadTranslator(model::Patient&);
		virtual ~PatientJSONLoadTranslator();

		void loadEntityFromJSON(const systelab::json::IJSONValue&);

	protected:
		model::Patient& m_patient;
	};

}}

