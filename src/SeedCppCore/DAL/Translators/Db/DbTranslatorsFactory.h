#pragma once

#include "IDbTranslatorsFactory.h"


namespace seed_cpp { namespace dal {

	class DbTranslatorsFactory : public IDbTranslatorsFactory
	{
	public:
		DbTranslatorsFactory();
		virtual ~DbTranslatorsFactory();

		std::unique_ptr<IDatabaseEntityTranslator> buildAddressTranslator(const std::string& patientId, model::Address&) const override;
		std::unique_ptr<IDatabaseEntityTranslator> buildAllergyTranslator(model::Allergy&) const override;
		std::unique_ptr<IDatabaseEntityTranslator> buildPatientTranslator(model::Patient&) const override;
		std::unique_ptr<IDatabaseEntityTranslator> buildUserTranslator(model::User&) const override;
	};

}}

