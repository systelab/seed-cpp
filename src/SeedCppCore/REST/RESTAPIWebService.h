#pragma once

#include "WebServerAdapterInterface/IWebService.h"

namespace systelab { namespace rest_api_core {
	class IEndpoint;
	class Router;
	class RoutesFactory;
}}

namespace seed_cpp { namespace rest {

	class IEndpointsFactory;

	class RESTAPIWebService : public systelab::web_server::IWebService
	{
	public:
		RESTAPIWebService(IEndpointsFactory&);
		virtual ~RESTAPIWebService();

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request&) const;

	private:
		enum class RouteAccess
		{
			ANONYMOUS = 0,
			BASIC = 1,
			ADMIN = 2
		};

		void addRoute(const std::string& method,
					  const std::string& uri,
					  const std::function<std::unique_ptr<systelab::rest_api_core::IEndpoint>()> endpointFactoryMethod,
					  RouteAccess access) const;

	private:
		IEndpointsFactory& m_endpointsFactory;
		std::unique_ptr<systelab::rest_api_core::Router> m_router;
		std::unique_ptr<systelab::rest_api_core::RoutesFactory> m_routesFactory;
	};

}}
