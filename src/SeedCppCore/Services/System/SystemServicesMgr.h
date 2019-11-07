#pragma once

namespace systelab { namespace rest_api_core {
	class IEpochTimeService;
}}

namespace seed_cpp { namespace service {

	class ISystemServicesFactory;

	class IResourceService;
	class ITimeService;
	class IUUIDGeneratorService;

	class SystemServicesMgr
	{
	public:
		SystemServicesMgr(service::ISystemServicesFactory&);
		virtual ~SystemServicesMgr();

		IResourceService& getResourceService() const;
		ITimeService& getTimeService() const;
		systelab::rest_api_core::IEpochTimeService& getEpochTimeService() const;
		IUUIDGeneratorService& getUUIDGeneratorService() const;

	private:
		ISystemServicesFactory& m_factory;

		mutable std::unique_ptr<IResourceService> m_resourceService;
		mutable std::unique_ptr<ITimeService> m_timeService;
		mutable std::unique_ptr<systelab::rest_api_core::IEpochTimeService> m_epochTimeService;
		mutable std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
	};

}}

