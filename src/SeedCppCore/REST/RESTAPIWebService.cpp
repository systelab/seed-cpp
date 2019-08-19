#include "stdafx.h"
#include "RESTAPIWebService.h"

#include "Model/Settings.h"
#include "REST/Endpoints/IEndpointsFactory.h"

#include "RESTAPICore/Router/IRoute.h"
#include "RESTAPICore/Router/Router.h"
#include "RESTAPICore/Router/RoutesFactory.h"
#include "RESTAPICore/Endpoint/IEndpoint.h"

#include "WebServerAdapterInterface/Model/Reply.h"
#include "WebServerAdapterInterface/Model/Request.h"


using namespace systelab::rest_api_core;

namespace seed_cpp { namespace rest {

	RESTAPIWebService::RESTAPIWebService(IEndpointsFactory& endpointsFactory)
		:m_endpointsFactory(endpointsFactory)
		,m_router(std::make_unique<systelab::rest_api_core::Router>())
		,m_routesFactory()
	{
		std::string jwtSecretKey = model::setting::JWT_SECRET_KEY;
		m_routesFactory = std::make_unique<systelab::rest_api_core::RoutesFactory>(jwtSecretKey);

		// Health
		addRoute("GET",    "seed/v1/health",            std::bind(&IEndpointsFactory::buildHealthGetEndpoint,       std::ref(m_endpointsFactory)), RouteAccess::ANONYMOUS);

		// Allergies
		addRoute("GET",    "seed/v1/allergies",         std::bind(&IEndpointsFactory::buildAllergiesGetAllEndpoint, std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("GET",    "seed/v1/allergies/:id",     std::bind(&IEndpointsFactory::buildAllergiesGetEndpoint,    std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("POST",   "seed/v1/allergies/allergy", std::bind(&IEndpointsFactory::buildAllergiesPostEndpoint,   std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("PUT",    "seed/v1/allergies/:id",     std::bind(&IEndpointsFactory::buildAllergiesPutEndpoint,    std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("DELETE", "seed/v1/allergies/:id",     std::bind(&IEndpointsFactory::buildAllergiesDeleteEndpoint, std::ref(m_endpointsFactory)), RouteAccess::BASIC);

		// Patients
		addRoute("GET",    "seed/v1/patients",          std::bind(&IEndpointsFactory::buildPatientsGetAllEndpoint,  std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("GET",    "seed/v1/patients/:id",      std::bind(&IEndpointsFactory::buildPatientsGetEndpoint,     std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("POST",   "seed/v1/patients/patient",  std::bind(&IEndpointsFactory::buildPatientsPostEndpoint,    std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("PUT",    "seed/v1/patients/:id",      std::bind(&IEndpointsFactory::buildPatientsPutEndpoint,     std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("DELETE", "seed/v1/patients/:id",      std::bind(&IEndpointsFactory::buildPatientsDeleteEndpoint,  std::ref(m_endpointsFactory)), RouteAccess::BASIC);

		// Users
		addRoute("GET",    "seed/v1/users",             std::bind(&IEndpointsFactory::buildUsersGetAllEndpoint,     std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("GET",    "seed/v1/users/:id",         std::bind(&IEndpointsFactory::buildUsersGetEndpoint,        std::ref(m_endpointsFactory)), RouteAccess::BASIC);
		addRoute("POST",   "seed/v1/users/user",        std::bind(&IEndpointsFactory::buildUsersPostEndpoint,       std::ref(m_endpointsFactory)), RouteAccess::ADMIN);
		addRoute("PUT",    "seed/v1/users/:id",         std::bind(&IEndpointsFactory::buildUsersPutEndpoint,        std::ref(m_endpointsFactory)), RouteAccess::ADMIN);
		addRoute("DELETE", "seed/v1/users/:id",         std::bind(&IEndpointsFactory::buildUsersDeleteEndpoint,     std::ref(m_endpointsFactory)), RouteAccess::ADMIN);
		addRoute("POST",   "seed/v1/users/login",       std::bind(&IEndpointsFactory::buildUsersLoginPostEndpoint,  std::ref(m_endpointsFactory)), RouteAccess::ADMIN);
	}

	RESTAPIWebService::~RESTAPIWebService() = default;

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

	void RESTAPIWebService::addRoute(const std::string& method,
									 const std::string& uri,
									 const std::function<std::unique_ptr<IEndpoint>()> endpointFactoryMethod,
									 RouteAccess /*access*/) const
	{
		auto route = m_routesFactory->buildRoute(method, uri, {}, endpointFactoryMethod);
		m_router->addRoute(std::move(route));
	}

}}
