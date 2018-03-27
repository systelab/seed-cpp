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

		std::unique_ptr<IEndpoint> buildPatientGetAllEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientGetEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientPostEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientPutEndpoint(const EndpointRequestData&);
		std::unique_ptr<IEndpoint> buildPatientDeleteEndpoint(const EndpointRequestData&);

	private:
		Core& m_core;
	};

}}

