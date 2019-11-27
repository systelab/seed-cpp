#include "stdafx.h"
#include "ContextBuilderService.h"

#include "Context.h"
#include "Agents/AgentsMgr.h"
#include "Agents/AgentsFactory.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "DAL/Translators/JSON/JSONTranslatorsFactory.h"
#include "Model/Model.h"
#include "REST/Endpoints/EndpointsFactory.h"
#include "REST/RouteAccess/RouteAccessValidatorsFactory.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/ModelServicesFactory.h"
#include "Services/Security/SecurityServicesFactory.h"
#include "Services/System/SystemServicesFactory.h"
#include "Services/Validator/ValidatorServicesFactory.h"


namespace seed_cpp { namespace service {

	ContextBuilderService::ContextBuilderService(Context& context)
		:m_context(context)
	{
	}

	ContextBuilderService::~ContextBuilderService() = default;

	void ContextBuilderService::buildModel()
	{
		auto model = std::make_unique<model::Model>();
		m_context.setModel(std::move(model));
	}

	void ContextBuilderService::buildFactories()
	{
		auto dbTranslatorsFactory = std::make_unique<dal::DbTranslatorsFactory>();
		auto dbDAOFactory = std::make_unique<dal::DbDAOFactory>(m_context);
		auto jsonTranslatorsFactory = std::make_unique<dal::JSONTranslatorsFactory>();
		auto modelServicesFactory = std::make_unique<service::ModelServicesFactory>(m_context);
		auto securityServicesFactory = std::make_unique<service::SecurityServicesFactory>(m_context);
		auto systemServicesFactory = std::make_unique<service::SystemServicesFactory>(m_context);
		auto validatorServicesFactory = std::make_unique<service::ValidatorServicesFactory>(m_context);
		auto agentsFactory = std::make_unique<agent::AgentsFactory>(m_context);
		auto endpointsFactory = std::make_unique<rest::EndpointsFactory>(m_context);
		auto routeAccessValidatorsFactory = std::make_unique<rest::RouteAccessValidatorsFactory>(m_context);

		m_context.setDbTranslatorsFactory(std::move(dbTranslatorsFactory));
		m_context.setDbDAOFactory(std::move(dbDAOFactory));
		m_context.setJSONTranslatorsFactory(std::move(jsonTranslatorsFactory));
		m_context.setModelServicesFactory(std::move(modelServicesFactory));
		m_context.setSecurityServicesFactory(std::move(securityServicesFactory));
		m_context.setSystemServicesFactory(std::move(systemServicesFactory));
		m_context.setValidatorServicesFactory(std::move(validatorServicesFactory));
		m_context.setAgentsFactory(std::move(agentsFactory));
		m_context.setEndpointsFactory(std::move(endpointsFactory));
		m_context.setRouteAccessValidatorsFactory(std::move(routeAccessValidatorsFactory));
	}

	void ContextBuilderService::buildServices()
	{
		auto servicesMgr = std::make_unique<service::ServicesMgr>(m_context);
		m_context.setServicesMgr(std::move(servicesMgr));
	}

	void ContextBuilderService::buildAgents()
	{
		auto agentsMgr = std::make_unique<agent::AgentsMgr>(m_context);
		m_context.setAgentsMgr(std::move(agentsMgr));
	}

}}
