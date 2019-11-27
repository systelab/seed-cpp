#pragma once

#include "WebServerAdapterInterface/IWebService.h"


namespace systelab { 
	namespace rest_api_core {
		class IEndpoint;
		class IRouteAccessValidator;
		class Router;
		class RoutesFactory;
	}
	namespace setting {
		class ISettingsService;
	}
}

namespace seed_cpp { namespace rest {

	class IEndpointsFactory;
	class IRouteAccessValidatorsFactory;

	class RESTAPIWebService : public systelab::web_server::IWebService
	{
	public:
		typedef std::function< std::unique_ptr<systelab::rest_api_core::IRouteAccessValidator>() > RouteAccessValidatorFactoryMethod;
		typedef std::function< std::unique_ptr<systelab::rest_api_core::IEndpoint>() > EndpointFactoryMethod;

	public:
		RESTAPIWebService(IEndpointsFactory&,
						  IRouteAccessValidatorsFactory&,
						  systelab::setting::ISettingsService&);
		virtual ~RESTAPIWebService();

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request&) const;

	private:
		enum class RouteAccess
		{
			ANONYMOUS = 0,
			BASIC = 1,
			ADMIN = 2
		};

		void addRoute(const std::string& method, const std::string& uri, const EndpointFactoryMethod, RouteAccess) const;
		std::vector<RouteAccessValidatorFactoryMethod> getRouteAccessValidators(RouteAccess) const;

		void traceRequest(const systelab::web_server::Request&, const systelab::web_server::Reply&) const;
		bool containsSensitiveData(const systelab::web_server::Request&) const;
		std::string formatContent(const std::string&) const;

	private:
		IEndpointsFactory& m_endpointsFactory;
		IRouteAccessValidatorsFactory& m_routeAccessValidatorsFactory;
		systelab::setting::ISettingsService& m_settingsService;

		std::unique_ptr<systelab::rest_api_core::Router> m_router;
		std::unique_ptr<systelab::rest_api_core::RoutesFactory> m_routesFactory;
	};

}}
