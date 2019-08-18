#pragma once

#include "REST/Endpoints/EntityPutEndpoint.h"
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

	class UsersPutEndpoint : public EntityPutEndpoint<model::User, service::IUserModelService>
	{
	public:
		UsersPutEndpoint(const dal::IJSONTranslatorsFactory&,
						 service::IUserModelService&,
						 const service::IJSONValidatorService&,
						 const systelab::json::IJSONAdapter&);
	};

}}
