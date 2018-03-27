#pragma once

#include <memory>


namespace seed_cpp { namespace rest {

	class EndpointRequestData;
	class IEndpoint;

	class IEndpointsFactory
	{
	public:
		virtual ~IEndpointsFactory() {};

		virtual std::unique_ptr<IEndpoint> buildPatientGetAllEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientGetEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientPostEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientPutEndpoint(const EndpointRequestData&) = 0;
		virtual std::unique_ptr<IEndpoint> buildPatientDeleteEndpoint(const EndpointRequestData&) = 0;
	};

}}

