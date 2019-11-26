#pragma once


namespace systelab { namespace trace {
	class IFileAgent;
}}

namespace seed_cpp { namespace agent {

	class IAgentsFactory
	{
	public:
		virtual ~IAgentsFactory() = default;

		virtual std::unique_ptr<systelab::trace::IFileAgent> buildTraceAgent(const std::string& channelName) const = 0;
	};

}}

