#pragma once

#include "IAgentsFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace agent {

	class AgentsFactory : public IAgentsFactory
	{
	public:
		AgentsFactory(Context&);
		virtual ~AgentsFactory();

		std::unique_ptr<systelab::trace::IFileAgent> buildTraceAgent(const std::string& channelName) const override;

	private:
		Context& m_context;
	};

}}

