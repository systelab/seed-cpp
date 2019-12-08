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

		std::unique_ptr<IResourceService> buildResourceService() const override;
		std::unique_ptr<ITimeService> buildTimeService() const override;
		std::unique_ptr<systelab::rest_api_core::IEpochTimeService> buildEpochTimeService() const override;
		std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const override;
		std::unique_ptr<systelab::setting::ISettingsService> buildSettingsService() const override;

	private:
		Context& m_context;
	};

}}

