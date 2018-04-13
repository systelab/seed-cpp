#pragma once

#include <memory>


namespace seed_cpp { namespace service {

	class IServicesFactory;

	class IBase64EncodeService;
	class ISignatureService;
	class IUserModelService;

	class ServicesMgr
	{
	public:
		ServicesMgr(service::IServicesFactory&);
		virtual ~ServicesMgr();

		// Model services
		IUserModelService& getUserModelService() const;

		// Security services
		ISignatureService& getSignatureService() const;
		IBase64EncodeService& getBase64EncodeService() const;

	private:
		IServicesFactory& m_servicesFactory;

		mutable std::unique_ptr<IUserModelService> m_userModelService;

		mutable std::unique_ptr<ISignatureService> m_signatureService;
		mutable std::unique_ptr<IBase64EncodeService> m_base64EncodeService;
	};

}}

