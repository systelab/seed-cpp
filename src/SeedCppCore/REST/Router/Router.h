#pragma once

#include "WebServerInterface/IWebService.h"

#include "REST/Endpoints/IEndpoint.h"
#include "REST/Router/RouteParam.h"

#include <memory>
#include <vector>


namespace systelab { namespace web_server {
	class Reply;
	class Request;
}}

namespace seed_cpp { namespace rest {

	class Route;

	class Router
	{
	public:
		Router();
		virtual ~Router();

		void addRoute(const std::string& method, const std::string& uri,
					  std::function< std::unique_ptr<IEndpoint>(const std::vector<RouteParam>&) > factoryMethod);

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request& request) const;

	private:
		std::vector< std::unique_ptr<Route> > m_routes;
	};

}}
