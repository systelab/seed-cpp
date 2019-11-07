#pragma once

#include "RESTAPICore/Endpoint/IEndpoint.h"


namespace seed_cpp { namespace rest {

	class HealthGetEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		HealthGetEndpoint();
		virtual ~HealthGetEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData&) override;
	};

}}

