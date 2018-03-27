#pragma once

#include "IJSONTranslatorsFactory.h"


namespace seed_cpp { namespace dal {

	class JSONTranslatorsFactory : public IJSONTranslatorsFactory
	{
	public:
		JSONTranslatorsFactory();
		virtual ~JSONTranslatorsFactory();

		std::unique_ptr<IJSONLoadTranslator> buildPatientLoadTranslator(model::Patient&) const;
		std::unique_ptr<IJSONSaveTranslator> buildPatientSaveTranslator(const model::Patient&) const;
	};

}}

