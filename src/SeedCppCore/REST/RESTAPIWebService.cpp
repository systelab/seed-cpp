#include "StdAfx.h"
#include "RESTAPIWebService.h"

#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/IEndpointsFactory.h"
#include "REST/Router/Router.h"

#include "WebServerInterface/Model/Reply.h"
#include "WebServerInterface/Model/Request.h"


namespace seed_cpp { namespace rest {

	RESTAPIWebService::RESTAPIWebService(IEndpointsFactory& endpointsFactory)
		:m_endpointsFactory(endpointsFactory)
	{
		using namespace std::placeholders;

		m_router = std::make_unique<Router>();
		m_router->addRoute("GET",  "seed/v1/patients",     std::bind(&IEndpointsFactory::buildPatientGetAllEndpoint, std::ref(m_endpointsFactory), _1));
		m_router->addRoute("GET",  "seed/v1/patients/:id", std::bind(&IEndpointsFactory::buildPatientGetEndpoint, std::ref(m_endpointsFactory), _1));
		m_router->addRoute("POST", "seed/v1/patients",     std::bind(&IEndpointsFactory::buildPatientPostEndpoint, std::ref(m_endpointsFactory), _1));
	}

	RESTAPIWebService::~RESTAPIWebService()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> RESTAPIWebService::process(const systelab::web_server::Request& request) const
	{
		return m_router->process(request);
	}

}}
