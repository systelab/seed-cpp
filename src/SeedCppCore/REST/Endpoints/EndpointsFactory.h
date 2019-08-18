#pragma once

#include "REST/Endpoints/IEndpointsFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace rest {

	using namespace systelab::rest_api_core;

	class EndpointsFactory : public IEndpointsFactory
	{
	public:
		EndpointsFactory(Context&);
		virtual ~EndpointsFactory();

		// Allergies
		std::unique_ptr<IEndpoint> buildAllergiesGetAllEndpoint() override;
		std::unique_ptr<IEndpoint> buildAllergiesGetEndpoint() override;
		std::unique_ptr<IEndpoint> buildAllergiesPostEndpoint() override;
		std::unique_ptr<IEndpoint> buildAllergiesPutEndpoint() override;
		std::unique_ptr<IEndpoint> buildAllergiesDeleteEndpoint() override;

		// Health
		std::unique_ptr<IEndpoint> buildHealthGetEndpoint() override;

		// Patients
		std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint() override;
		std::unique_ptr<IEndpoint> buildPatientsGetEndpoint() override;
		std::unique_ptr<IEndpoint> buildPatientsPostEndpoint() override;
		std::unique_ptr<IEndpoint> buildPatientsPutEndpoint() override;
		std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint() override;

		// Users
		std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint() override;
		std::unique_ptr<IEndpoint> buildUsersGetEndpoint() override;
		std::unique_ptr<IEndpoint> buildUsersPostEndpoint() override;
		std::unique_ptr<IEndpoint> buildUsersPutEndpoint() override;
		std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint() override;
		std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint() override;

	private:
		Context& m_context;
	};

}}

