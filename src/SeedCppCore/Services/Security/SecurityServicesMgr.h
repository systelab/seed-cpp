#pragma once

namespace systelab { namespace jwt {
	class ITokenBuilderService;
	class ITokenParserService;
}}

namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService;
	class ISecurityServicesFactory;

	class SecurityServicesMgr
	{
	public:
		SecurityServicesMgr(service::ISecurityServicesFactory&);
		virtual ~SecurityServicesMgr();

		IAuthorizationValidatorService& getAuthorizationValidatorService() const;
		systelab::jwt::ITokenBuilderService& getJWTTokenBuilderService() const;
		systelab::jwt::ITokenParserService& getJWTTokenParserService() const;

	private:
		ISecurityServicesFactory& m_factory;

		mutable std::unique_ptr<IAuthorizationValidatorService> m_authorizationValidatorService;
		mutable std::unique_ptr<systelab::jwt::ITokenBuilderService> m_jwtTokenBuilderService;
		mutable std::unique_ptr<systelab::jwt::ITokenParserService> m_jwtTokenParserService;
	};

}}

