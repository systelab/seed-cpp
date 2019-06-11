#include "stdafx.h"
#include "HealthGetEndpoint.h"

#include "REST/Helpers/ReplyBuilderHelper.h"


namespace seed_cpp { namespace rest {

	HealthGetEndpoint::HealthGetEndpoint()
	{
	}
	
	HealthGetEndpoint::~HealthGetEndpoint() = default;

	bool HealthGetEndpoint::hasAccess() const
	{
		return true;
	}

	std::unique_ptr<systelab::web_server::Reply> HealthGetEndpoint::execute()
	{
		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, {});
	}

}}

