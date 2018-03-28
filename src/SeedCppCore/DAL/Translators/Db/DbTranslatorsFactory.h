#pragma once

#include "IDbTranslatorsFactory.h"


namespace seed_cpp { namespace dal {

	class DbTranslatorsFactory : public IDbTranslatorsFactory
	{
	public:
		DbTranslatorsFactory();
		virtual ~DbTranslatorsFactory();

		std::unique_ptr<IDatabaseEntityTranslator> buildPatientTranslator(model::Patient&) const;
		std::unique_ptr<IDatabaseEntityTranslator> buildAddressTranslator(unsigned int patientId, model::Address&) const;
		std::unique_ptr<IDatabaseEntityTranslator> buildUserTranslator(model::User&) const;
	};

}}

