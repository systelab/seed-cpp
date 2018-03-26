#pragma once

#include "REST/Endpoints/IEndpointsFactory.h"


namespace seed_cpp {
	class Core;
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class EndpointsFactory : public IEndpointsFactory
	{
	public:
		EndpointsFactory(Core&);
		virtual ~EndpointsFactory();

		std::unique_ptr<IEndpoint> buildPatientGETAllEndpoint(const std::vector<RouteParam>&);
		std::unique_ptr<IEndpoint> buildPatientGETEndpoint(const std::vector<RouteParam>&);
		std::unique_ptr<IEndpoint> buildPatientPOSTEndpoint(const std::vector<RouteParam>&);
		std::unique_ptr<IEndpoint> buildPatientPUTEndpoint(const std::vector<RouteParam>&);
		std::unique_ptr<IEndpoint> buildPatientDELETEEndpoint(const std::vector<RouteParam>&);

	private:
		Core& m_core;
	};

}}

