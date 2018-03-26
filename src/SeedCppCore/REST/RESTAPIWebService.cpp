#include "StdAfx.h"
#include "RESTAPIWebService.h"

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
		m_router->addRoute("GET", "rest/api/patients", std::bind(&IEndpointsFactory::buildPatientGETAllEndpoint, std::ref(m_endpointsFactory), _1) );
	}

	RESTAPIWebService::~RESTAPIWebService()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> RESTAPIWebService::process(const systelab::web_server::Request& request) const
	{
		return std::unique_ptr<systelab::web_server::Reply>();
	}

}}
