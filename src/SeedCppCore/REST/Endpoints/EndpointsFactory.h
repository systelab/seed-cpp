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

		// Allergies
		std::unique_ptr<IEndpoint> buildAllergiesGetAllEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildAllergiesGetEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildAllergiesPostEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildAllergiesPutEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildAllergiesDeleteEndpoint(const EndpointRequestData&) override;

		// Patients
		std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildPatientsGetEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildPatientsPostEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildPatientsPutEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint(const EndpointRequestData&) override;

		// Users
		std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildUsersGetEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildUsersPostEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildUsersPutEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint(const EndpointRequestData&) override;
		std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint(const EndpointRequestData&) override;

	private:
		Core& m_core;
	};

}}

