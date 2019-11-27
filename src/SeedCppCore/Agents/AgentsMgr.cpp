#include "stdafx.h"
#include "AgentsMgr.h"

#include "Context.h"
#include "Agents/IAgentsFactory.h"

#include "TraceAPI/IFileAgent.h"


namespace seed_cpp { namespace agent {

	AgentsMgr::AgentsMgr(Context& context)
		:m_context(context)
		,m_traceAgents()
	{
	}

	AgentsMgr::~AgentsMgr() = default;

	void AgentsMgr::initialize()
	{
		auto& agentsFactory = *m_context.getAgentsFactory();
		m_traceAgents.emplace("RESTAPI", agentsFactory.buildTraceAgent("RESTAPI"));
		m_traceAgents.emplace("Error", agentsFactory.buildTraceAgent("Error"));
	}

}}

