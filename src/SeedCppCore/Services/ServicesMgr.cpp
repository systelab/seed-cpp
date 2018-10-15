#include "StdAfx.h"
#include "ServicesMgr.h"

#include "Services/IServicesFactory.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/IJWTBuilderService.h"
#include "Services/Security/IJWTValidatorService.h"
#include "Services/Security/ISignatureService.h"
#include "Services/System/ITimeService.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(service::IServicesFactory& factory)
		:m_servicesFactory(factory)
		,m_userModelService()
		,m_authorizationValidatorService()
		,m_jwtBuilderService()
		,m_jwtValidatorService()
		,m_signatureService()
		,m_base64EncodeService()
		,m_timeService()
	{
	}
	
	ServicesMgr::~ServicesMgr()
	{
	}

	IUserModelService& ServicesMgr::getUserModelService() const
	{
		if (!m_userModelService.get())
		{
			m_userModelService = m_servicesFactory.buildUserModelService();
		}

		return *m_userModelService;
	}

	IAuthorizationValidatorService& ServicesMgr::getAuthorizationValidatorService() const
	{
		if (!m_authorizationValidatorService.get())
		{
			m_authorizationValidatorService = m_servicesFactory.buildAuthorizationValidatorService();
		}

		return *m_authorizationValidatorService;
	}

	IJWTBuilderService& ServicesMgr::getJWTBuilderService() const
	{
		if (!m_jwtBuilderService.get())
		{
			m_jwtBuilderService = m_servicesFactory.buildJWTBuilderService();
		}

		return *m_jwtBuilderService;
	}

	IJWTValidatorService& ServicesMgr::getJWTValidatorService() const
	{
		if (!m_jwtValidatorService.get())
		{
			m_jwtValidatorService = m_servicesFactory.buildJWTValidatorService();
		}

		return *m_jwtValidatorService;
	}

	ISignatureService& ServicesMgr::getSignatureService() const
	{
		if (!m_signatureService.get())
		{
			m_signatureService = m_servicesFactory.buildSignatureService();
		}

		return *m_signatureService;
	}

	IBase64EncodeService& ServicesMgr::getBase64EncodeService() const
	{
		if (!m_base64EncodeService.get())
		{
			m_base64EncodeService = m_servicesFactory.buildBase64EncodeService();
		}

		return *m_base64EncodeService;
	}

	ITimeService& ServicesMgr::getTimeService() const
	{
		if (!m_timeService.get())
		{
			m_timeService = m_servicesFactory.buildTimeService();
		}

		return *m_timeService;
	}

}}

