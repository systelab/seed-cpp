#pragma once

namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class IContextBuilderService
	{
	public:
		virtual void buildFactories() = 0;
		virtual void buildModel() = 0;
		virtual void buildServices() = 0;
	};

}}