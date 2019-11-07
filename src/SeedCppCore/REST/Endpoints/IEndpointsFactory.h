#pragma once

#include <memory>

#include "RESTAPICore/Endpoint/IEndpoint.h"


namespace seed_cpp { namespace rest {

	using namespace systelab::rest_api_core;

	class IEndpointsFactory
	{
	public:
		virtual ~IEndpointsFactory() = default;

		// Health
		virtual std::unique_ptr<IEndpoint> buildHealthGetEndpoint() const = 0;

		// Allergies
		virtual std::unique_ptr<IEndpoint> buildAllergiesGetAllEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesGetEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesPostEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesPutEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesDeleteEndpoint() const = 0;

		// Patients
		virtual std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsGetEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPostEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPutEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint() const = 0;

		// Users
		virtual std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersGetEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPostEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPutEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint() const = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint() const = 0;
	};

}}

