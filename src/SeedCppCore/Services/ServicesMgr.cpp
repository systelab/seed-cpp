#include "stdafx.h"
#include "ServicesMgr.h"

#include "Services/IServicesFactory.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/IJWTBuilderService.h"
#include "Services/Security/IJWTValidatorService.h"
#include "Services/Security/ISignatureService.h"
#include "Services/System/IResourceService.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"
#include "Services/Validator/IJSONValidatorService.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(service::IServicesFactory& factory)
		:m_servicesFactory(factory)
		,m_patientModelService()
		,m_userModelService()
		,m_authorizationValidatorService()
		,m_jwtBuilderService()
		,m_jwtValidatorService()
		,m_signatureService()
		,m_base64EncodeService()
		,m_jsonValidatorService()
		,m_resourceService()
		,m_timeService()
		,m_uuidGeneratorService()
	{
	}
	
	ServicesMgr::~ServicesMgr()
	{
	}


	// Model services
	IPatientModelService& ServicesMgr::getPatientModelService() const
	{
		if (!m_patientModelService.get())
		{
			m_patientModelService = m_servicesFactory.buildPatientModelService();
		}

		return *m_patientModelService;
	}

	IUserModelService& ServicesMgr::getUserModelService() const
	{
		if (!m_userModelService.get())
		{
			m_userModelService = m_servicesFactory.buildUserModelService();
		}

		return *m_userModelService;
	}


	// Security services
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


	// Validator services
	IJSONValidatorService& ServicesMgr::getJSONValidatorService() const
	{
		if (!m_jsonValidatorService.get())
		{
			m_jsonValidatorService = m_servicesFactory.buildJSONValidatorService();
		}

		return *m_jsonValidatorService;
	}


	// System services
	IResourceService& ServicesMgr::getResourceService() const
	{
		if (!m_resourceService.get())
		{
			m_resourceService = m_servicesFactory.buildResourceService();
		}

		return *m_resourceService;
	}

	ITimeService& ServicesMgr::getTimeService() const
	{
		if (!m_timeService.get())
		{
			m_timeService = m_servicesFactory.buildTimeService();
		}

		return *m_timeService;
	}

	IUUIDGeneratorService& ServicesMgr::getUUIDGeneratorService() const
	{
		if (!m_uuidGeneratorService.get())
		{
			m_uuidGeneratorService = m_servicesFactory.buildUUIDGeneratorService();
		}

		return *m_uuidGeneratorService;
	}

}}

