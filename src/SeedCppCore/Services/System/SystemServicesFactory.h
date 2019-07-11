#pragma once

#include "ISystemServicesFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class SystemServicesFactory : public ISystemServicesFactory
	{
	public:
		SystemServicesFactory(Context&);
		virtual ~SystemServicesFactory();

		std::unique_ptr<IResourceService> buildResourceService() const;
		std::unique_ptr<ITimeService> buildTimeService() const;
		std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const;

	private:
		Context& m_context;
	};

}}

