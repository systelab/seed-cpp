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

		// Patients
		m_router->addRoute("GET",    "seed/v1/patients",         std::bind(&IEndpointsFactory::buildPatientsGetAllEndpoint, std::ref(m_endpointsFactory), _1));
		m_router->addRoute("GET",    "seed/v1/patients/:id",     std::bind(&IEndpointsFactory::buildPatientsGetEndpoint,    std::ref(m_endpointsFactory), _1));
		m_router->addRoute("POST",   "seed/v1/patients/patient", std::bind(&IEndpointsFactory::buildPatientsPostEndpoint,   std::ref(m_endpointsFactory), _1));
		m_router->addRoute("PUT",    "seed/v1/patients/:id",     std::bind(&IEndpointsFactory::buildPatientsPutEndpoint,    std::ref(m_endpointsFactory), _1));
		m_router->addRoute("DELETE", "seed/v1/patients/:id",     std::bind(&IEndpointsFactory::buildPatientsDeleteEndpoint, std::ref(m_endpointsFactory), _1));

		// Users
		m_router->addRoute("POST",   "seed/v1/users/login",      std::bind(&IEndpointsFactory::buildUsersLoginPostEndpoint, std::ref(m_endpointsFactory), _1));
	}

	RESTAPIWebService::~RESTAPIWebService()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> RESTAPIWebService::process(const systelab::web_server::Request& request) const
	{
		if (request.getMethod() == "OPTIONS")
		{
			auto preflightReply = std::make_unique<systelab::web_server::Reply>();
			preflightReply->setStatus(systelab::web_server::Reply::OK);
			preflightReply->setContent("");

			return preflightReply;
		}
		else
		{
			return m_router->process(request);
		}
	}

}}
