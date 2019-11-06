#include "stdafx.h"
#include "HealthGetEndpoint.h"

#include "REST/Helpers/ReplyBuilderHelper.h"


using namespace systelab::rest_api_core;

namespace seed_cpp { namespace rest {

	HealthGetEndpoint::HealthGetEndpoint()
	{
	}
	
	HealthGetEndpoint::~HealthGetEndpoint() = default;

	std::unique_ptr<systelab::web_server::Reply> HealthGetEndpoint::execute(const EndpointRequestData&)
	{
		return ReplyBuilderHelper::buildEmpty(systelab::web_server::Reply::OK);
	}

}}

