#include "Router.h"

#include "REST/Router/Route.h"

#include "Model/Reply.h"
#include "Model/Request.h"


namespace seed_cpp { namespace rest {

	Router::Router()
	{
	}

	Router::~Router()
	{
	}

	void Router::addRoute(const std::string& method,
						  const std::string& uri,
						  std::function< std::unique_ptr<IEndpoint>(const EndpointRequestData&) > factoryMethod)
	{
		std::unique_ptr<Route> route = std::make_unique<Route>(method, uri, factoryMethod);
		m_routes.push_back(std::move(route));
	}

	std::unique_ptr<systelab::web_server::Reply> Router::process(const systelab::web_server::Request& request) const
	{
		for (const auto& route : m_routes)
		{
			std::unique_ptr<systelab::web_server::Reply> reply = route->execute(request);
			if (reply)
			{
				return std::move(reply);
			}
		}

		return std::unique_ptr<systelab::web_server::Reply>();
	}

}}
