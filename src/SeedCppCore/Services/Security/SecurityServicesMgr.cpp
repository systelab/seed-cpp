#include "stdafx.h"
#include "SecurityServicesMgr.h"

#include "Services/Security/ISecurityServicesFactory.h"

#include "JWTUtils/Services/ITokenBuilderService.h"
#include "JWTUtils/Services/ITokenParserService.h"


namespace seed_cpp { namespace service {

	SecurityServicesMgr::SecurityServicesMgr(service::ISecurityServicesFactory& factory)
		:m_factory(factory)
	{
	}
	
	SecurityServicesMgr::~SecurityServicesMgr() = default;

	systelab::jwt::ITokenBuilderService& SecurityServicesMgr::getJWTTokenBuilderService() const
	{
		if (!m_jwtTokenBuilderService)
		{
			m_jwtTokenBuilderService = m_factory.buildJWTTokenBuilderService();
		}

		return *m_jwtTokenBuilderService;
	}

	systelab::jwt::ITokenParserService& SecurityServicesMgr::getJWTTokenParserService() const
	{
		if (!m_jwtTokenParserService)
		{
			m_jwtTokenParserService = m_factory.buildJWTTokenParserService();
		}

		return *m_jwtTokenParserService;
	}

}}
