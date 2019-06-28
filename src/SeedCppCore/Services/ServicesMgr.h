#pragma once

namespace systelab { namespace jwt {
	class ITokenBuilderService;
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class IServicesFactory;

	class IAllergyModelService;
	class IAuthorizationValidatorService;
	class IJSONValidatorService;
	class IPatientModelService;
	class IResourceService;
	class ITimeService;
	class IUserModelService;
	class IUUIDGeneratorService;

	class ServicesMgr
	{
	public:
		ServicesMgr(service::IServicesFactory&);
		virtual ~ServicesMgr();

		// Model services
		IAllergyModelService& getAllergyModelService() const;
		IPatientModelService& getPatientModelService() const;
		IUserModelService& getUserModelService() const;

		// Security services
		IAuthorizationValidatorService& getAuthorizationValidatorService() const;
		systelab::jwt::ITokenBuilderService& getJWTTokenBuilderService() const;
		systelab::jwt::ITokenParserService& getJWTTokenParserService() const;

		// Validator services
		IJSONValidatorService& getJSONValidatorService() const;

		// System services
		IResourceService& getResourceService() const;
		ITimeService& getTimeService() const;
		IUUIDGeneratorService& getUUIDGeneratorService() const;

	private:
		IServicesFactory& m_servicesFactory;

		mutable std::unique_ptr<IAllergyModelService> m_allergyModelService;
		mutable std::unique_ptr<IPatientModelService> m_patientModelService;
		mutable std::unique_ptr<IUserModelService> m_userModelService;

		mutable std::unique_ptr<IAuthorizationValidatorService> m_authorizationValidatorService;
		mutable std::unique_ptr<systelab::jwt::ITokenBuilderService> m_jwtTokenBuilderService;
		mutable std::unique_ptr<systelab::jwt::ITokenParserService> m_jwtTokenParserService;

		mutable std::unique_ptr<IJSONValidatorService> m_jsonValidatorService;

		mutable std::unique_ptr<IResourceService> m_resourceService;
		mutable std::unique_ptr<ITimeService> m_timeService;
		mutable std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
	};

}}

