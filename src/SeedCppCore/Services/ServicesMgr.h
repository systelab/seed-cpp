#pragma once

#include <memory>


namespace seed_cpp { namespace service {

	class IServicesFactory;
	class IUserModelService;

	class ServicesMgr
	{
	public:
		ServicesMgr(service::IServicesFactory&);
		virtual ~ServicesMgr();

		service::IUserModelService& getUserModelService() const;

	private:
		service::IServicesFactory& m_servicesFactory;

		mutable std::unique_ptr<service::IUserModelService> m_userModelService;
	};

}}

