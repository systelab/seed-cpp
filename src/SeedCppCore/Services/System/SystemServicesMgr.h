#pragma once

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
		IUUIDGeneratorService& getUUIDGeneratorService() const;

	private:
		ISystemServicesFactory& m_factory;

		mutable std::unique_ptr<IResourceService> m_resourceService;
		mutable std::unique_ptr<ITimeService> m_timeService;
		mutable std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
	};

}}

