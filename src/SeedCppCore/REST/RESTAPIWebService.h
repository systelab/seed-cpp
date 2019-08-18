#pragma once

#include "WebServerAdapterInterface/IWebService.h"

namespace systelab { namespace rest_api_core {
	class Router;
}}

namespace seed_cpp { namespace rest {

	class IEndpointsFactory;

	class RESTAPIWebService : public systelab::web_server::IWebService
	{
	public:
		RESTAPIWebService(IEndpointsFactory&);
		virtual ~RESTAPIWebService();

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request& request) const;

	private:
		IEndpointsFactory& m_endpointsFactory;
		std::unique_ptr<systelab::rest_api_core::Router> m_router;
	};

}}
