#pragma once

#include <memory>


namespace seed_cpp { namespace rest {

	class EndpointRequestData;
	class IEndpoint;

	class IEndpointsFactory
	{
	public:
		virtual ~IEndpointsFactory() {};

		// Patients
		virtual std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsGetEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPostEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsPutEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint(const EndpointRequestData&) = 0;

		// Users
		virtual std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersGetEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPostEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersPutEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint(const EndpointRequestData&) = 0;
	};

}}

