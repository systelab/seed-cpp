#pragma once

#include <memory>


namespace seed_cpp { namespace model {
	class Address;
	class Allergy;
	class Patient;
	class User;
}}

namespace seed_cpp { namespace dal {

	class IDatabaseEntityTranslator;

	class IDbTranslatorsFactory
	{
	public:
		virtual ~IDbTranslatorsFactory() = default;

		virtual std::unique_ptr<IDatabaseEntityTranslator> buildAddressTranslator(const std::string& patientId, model::Address&) const = 0;
		virtual std::unique_ptr<IDatabaseEntityTranslator> buildAllergyTranslator(model::Allergy&) const = 0;
		virtual std::unique_ptr<IDatabaseEntityTranslator> buildPatientTranslator(model::Patient&) const = 0;
		virtual std::unique_ptr<IDatabaseEntityTranslator> buildUserTranslator(model::User&) const = 0;
	};

}}
