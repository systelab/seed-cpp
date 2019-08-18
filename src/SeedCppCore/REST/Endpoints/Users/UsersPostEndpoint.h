#pragma once

#include "REST/Endpoints/EntityPostEndpoint.h"

#include "Model/User.h"
#include "Services/Model/IUserModelService.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace service {
		class IJSONValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class UsersPostEndpoint : public EntityPostEndpoint<model::User, service::IUserModelService>
	{
	public:
		UsersPostEndpoint(const dal::IJSONTranslatorsFactory&,
						  service::IUserModelService&,
						  const service::IJSONValidatorService&,
						  const systelab::json::IJSONAdapter&);
	};

}}
