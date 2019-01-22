#pragma once

#include "REST/Endpoints/IEndpointsFactory.h"


namespace seed_cpp {
	class Core;
}

namespace seed_cpp { namespace rest {

	class EndpointsFactory : public IEndpointsFactory
	{
	public:
		EndpointsFactory(Core&);
		virtual ~EndpointsFactory();

		// Patients
		std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientsGetEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientsPostEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientsPutEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint(const EndpointRequestData&);

		// Users
		std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildUsersGetEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildUsersPostEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildUsersPutEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint(const EndpointRequestData&);

	private:
		Core& m_core;
	};

}}

