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
		virtual std::unique_ptr<IEndpoint> buildHealthGetEndpoint() = 0;

		// Allergies
		virtual std::unique_ptr<IEndpoint> buildAllergiesGetAllEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesGetEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesPostEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesPutEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildAllergiesDeleteEndpoint() = 0;

		// Patients
		virtual std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsGetEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPostEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPutEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint() = 0;

		// Users
		virtual std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersGetEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPostEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPutEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint() = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint() = 0;
	};

}}

