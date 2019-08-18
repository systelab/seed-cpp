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
		std::unique_ptr<IEndpoint> buildAllergiesGetAllEndpoint() const override;
		std::unique_ptr<IEndpoint> buildAllergiesGetEndpoint() const override;
		std::unique_ptr<IEndpoint> buildAllergiesPostEndpoint() const override;
		std::unique_ptr<IEndpoint> buildAllergiesPutEndpoint() const override;
		std::unique_ptr<IEndpoint> buildAllergiesDeleteEndpoint() const override;

		// Health
		std::unique_ptr<IEndpoint> buildHealthGetEndpoint() const override;

		// Patients
		std::unique_ptr<IEndpoint> buildPatientsGetAllEndpoint() const override;
		std::unique_ptr<IEndpoint> buildPatientsGetEndpoint() const override;
		std::unique_ptr<IEndpoint> buildPatientsPostEndpoint() const override;
		std::unique_ptr<IEndpoint> buildPatientsPutEndpoint() const override;
		std::unique_ptr<IEndpoint> buildPatientsDeleteEndpoint() const override;

		// Users
		std::unique_ptr<IEndpoint> buildUsersGetAllEndpoint() const override;
		std::unique_ptr<IEndpoint> buildUsersGetEndpoint() const override;
		std::unique_ptr<IEndpoint> buildUsersPostEndpoint() const override;
		std::unique_ptr<IEndpoint> buildUsersPutEndpoint() const override;
		std::unique_ptr<IEndpoint> buildUsersDeleteEndpoint() const override;
		std::unique_ptr<IEndpoint> buildUsersLoginPostEndpoint() const override;

	private:
		Context& m_context;
	};

}}

