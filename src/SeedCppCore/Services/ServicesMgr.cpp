#include "stdafx.h"
#include "ServicesMgr.h"

#include "Services/IServicesFactory.h"
#include "Services/Model/IAllergyModelService.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/System/IResourceService.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JWTUtils/Services/ITokenBuilderService.h"
#include "JWTUtils/Services/ITokenParserService.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(service::IServicesFactory& factory)
		:m_servicesFactory(factory)
	{
	}
	
	ServicesMgr::~ServicesMgr() = default;


	// Model services
	IAllergyModelService& ServicesMgr::getAllergyModelService() const
	{
		if (!m_allergyModelService)
		{
			m_allergyModelService = m_servicesFactory.buildAllergyModelService();
		}

		return *m_allergyModelService;
	}

	IPatientModelService& ServicesMgr::getPatientModelService() const
	{
		if (!m_patientModelService)
		{
			m_patientModelService = m_servicesFactory.buildPatientModelService();
		}

		return *m_patientModelService;
	}

	IUserModelService& ServicesMgr::getUserModelService() const
	{
		if (!m_userModelService)
		{
			m_userModelService = m_servicesFactory.buildUserModelService();
		}

		return *m_userModelService;
	}


	// Security services
	IAuthorizationValidatorService& ServicesMgr::getAuthorizationValidatorService() const
	{
		if (!m_authorizationValidatorService)
		{
			m_authorizationValidatorService = m_servicesFactory.buildAuthorizationValidatorService();
		}

		return *m_authorizationValidatorService;
	}

	systelab::jwt::ITokenBuilderService& ServicesMgr::getJWTTokenBuilderService() const
	{
		if (!m_jwtTokenBuilderService)
		{
			m_jwtTokenBuilderService = m_servicesFactory.buildJWTTokenBuilderService();
		}

		return *m_jwtTokenBuilderService;
	}

	systelab::jwt::ITokenParserService& ServicesMgr::getJWTTokenParserService() const
	{
		if (!m_jwtTokenParserService)
		{
			m_jwtTokenParserService = m_servicesFactory.buildJWTTokenParserService();
		}

		return *m_jwtTokenParserService;
	}


	// Validator services
	IJSONValidatorService& ServicesMgr::getJSONValidatorService() const
	{
		if (!m_jsonValidatorService)
		{
			m_jsonValidatorService = m_servicesFactory.buildJSONValidatorService();
		}

		return *m_jsonValidatorService;
	}


	// System services
	IResourceService& ServicesMgr::getResourceService() const
	{
		if (!m_resourceService)
		{
			m_resourceService = m_servicesFactory.buildResourceService();
		}

		return *m_resourceService;
	}

	ITimeService& ServicesMgr::getTimeService() const
	{
		if (!m_timeService)
		{
			m_timeService = m_servicesFactory.buildTimeService();
		}

		return *m_timeService;
	}

	IUUIDGeneratorService& ServicesMgr::getUUIDGeneratorService() const
	{
		if (!m_uuidGeneratorService)
		{
			m_uuidGeneratorService = m_servicesFactory.buildUUIDGeneratorService();
		}

		return *m_uuidGeneratorService;
	}

}}

