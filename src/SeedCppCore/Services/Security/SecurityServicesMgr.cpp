#include "stdafx.h"
#include "SecurityServicesMgr.h"

#include "Services/Security/ISecurityServicesFactory.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "JWTUtils/Services/ITokenBuilderService.h"
#include "JWTUtils/Services/ITokenParserService.h"


namespace seed_cpp { namespace service {

	SecurityServicesMgr::SecurityServicesMgr(service::ISecurityServicesFactory& factory)
		:m_factory(factory)
		,m_authorizationValidatorService()
		,m_jwtTokenBuilderService()
		,m_jwtTokenParserService()
	{
	}
	
	SecurityServicesMgr::~SecurityServicesMgr() = default;

	IAuthorizationValidatorService& SecurityServicesMgr::getAuthorizationValidatorService() const
	{
		if (!m_authorizationValidatorService.get())
		{
			m_authorizationValidatorService = m_factory.buildAuthorizationValidatorService();
		}

		return *m_authorizationValidatorService;
	}

	systelab::jwt::ITokenBuilderService& SecurityServicesMgr::getJWTTokenBuilderService() const
	{
		if (!m_jwtTokenBuilderService.get())
		{
			m_jwtTokenBuilderService = m_factory.buildJWTTokenBuilderService();
		}

		return *m_jwtTokenBuilderService;
	}

	systelab::jwt::ITokenParserService& SecurityServicesMgr::getJWTTokenParserService() const
	{
		if (!m_jwtTokenParserService.get())
		{
			m_jwtTokenParserService = m_factory.buildJWTTokenParserService();
		}

		return *m_jwtTokenParserService;
	}

}}
