#pragma once

#include <memory>


namespace seed_cpp { namespace service {

	class IServicesFactory;

	class IAuthorizationValidatorService;
	class IBase64EncodeService;
	class IJSONValidatorService;
	class IJWTBuilderService;
	class IJWTValidatorService;
	class IPatientModelService;
	class IResourceService;
	class ISignatureService;
	class ITimeService;
	class IUserModelService;
	class IUUIDGeneratorService;

	class ServicesMgr
	{
	public:
		ServicesMgr(service::IServicesFactory&);
		virtual ~ServicesMgr();

		// Model services
		IPatientModelService& getPatientModelService() const;
		IUserModelService& getUserModelService() const;

		// Security services
		IAuthorizationValidatorService& getAuthorizationValidatorService() const;
		IJWTBuilderService& getJWTBuilderService() const;
		IJWTValidatorService& getJWTValidatorService() const;
		ISignatureService& getSignatureService() const;
		IBase64EncodeService& getBase64EncodeService() const;

		// Validator services
		IJSONValidatorService& getJSONValidatorService() const;

		// System services
		IResourceService& getResourceService() const;
		ITimeService& getTimeService() const;
		IUUIDGeneratorService& getUUIDGeneratorService() const;

	private:
		IServicesFactory& m_servicesFactory;

		mutable std::unique_ptr<IPatientModelService> m_patientModelService;
		mutable std::unique_ptr<IUserModelService> m_userModelService;

		mutable std::unique_ptr<IAuthorizationValidatorService> m_authorizationValidatorService;
		mutable std::unique_ptr<IJWTBuilderService> m_jwtBuilderService;
		mutable std::unique_ptr<IJWTValidatorService> m_jwtValidatorService;
		mutable std::unique_ptr<ISignatureService> m_signatureService;
		mutable std::unique_ptr<IBase64EncodeService> m_base64EncodeService;

		mutable std::unique_ptr<IJSONValidatorService> m_jsonValidatorService;

		mutable std::unique_ptr<IResourceService> m_resourceService;
		mutable std::unique_ptr<ITimeService> m_timeService;
		mutable std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
	};

}}

