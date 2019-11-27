#pragma once

namespace systelab { namespace trace {
	class IFileAgent;
}}

namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace agent {

	class AgentsMgr
	{
	public:
		AgentsMgr(Context&);
		virtual ~AgentsMgr();

		void initialize();

	private:
		Context& m_context;

		std::map< std::string, std::unique_ptr<systelab::trace::IFileAgent> > m_traceAgents;
	};

}}

