#pragma once

#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp { namespace rest {

	class HealthGetEndpoint : public IEndpoint
	{
	public:
		HealthGetEndpoint();
		virtual ~HealthGetEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();
	};

}}

