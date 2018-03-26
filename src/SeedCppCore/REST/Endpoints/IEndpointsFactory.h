#pragma once

#include "REST/Router/RouteParam.h"

#include <memory>
#include <vector>

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class IEndpointsFactory
	{
	public:
		virtual ~IEndpointsFactory() {};

		virtual std::unique_ptr<IEndpoint> buildPatientGETAllEndpoint(const std::vector<RouteParam>&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientGETEndpoint(const std::vector<RouteParam>&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientPOSTEndpoint(const std::vector<RouteParam>&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientPUTEndpoint(const std::vector<RouteParam>&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientDELETEEndpoint(const std::vector<RouteParam>&) = 0;
	};

}}

