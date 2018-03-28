#pragma once

#include <memory>


namespace seed_cpp { namespace model {
	class Address;
	class Patient;
	class User;
}}

namespace seed_cpp { namespace dal {

	class IDatabaseEntityTranslator;

	class IDbTranslatorsFactory
	{
	public:
		virtual ~IDbTranslatorsFactory(){}

		virtual std::unique_ptr<IDatabaseEntityTranslator> buildPatientTranslator(model::Patient&) const = 0;
		virtual std::unique_ptr<IDatabaseEntityTranslator> buildAddressTranslator(unsigned int patientId, model::Address&) const = 0;
		virtual std::unique_ptr<IDatabaseEntityTranslator> buildUserTranslator(model::User&) const = 0;
	};

}}
