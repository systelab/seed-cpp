#include "stdafx.h"
#include "ServicesFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/PatientModelService.h"
#include "Services/Model/UserModelService.h"
#include "Services/Security/AuthorizationValidatorService.h"
#include "Services/System/ResourceService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"
#include "Services/Validator/JSONValidatorService.h"

#include "JWTUtils/Services/TokenBuilderService.h"
#include "JWTUtils/Services/TokenParserService.h"


namespace seed_cpp { namespace service {

	ServicesFactory::ServicesFactory(Core& core)
		:m_core(core)
	{
	}
	
	ServicesFactory::~ServicesFactory()
	{
	}

	// Model services
	std::unique_ptr<IPatientModelService> ServicesFactory::buildPatientModelService() const
	{
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		IUUIDGeneratorService& uuidGeneratorService = m_core.getServicesMgr().getUUIDGeneratorService();
		ITimeService& timeService = m_core.getServicesMgr().getTimeService();

		return std::make_unique<PatientModelService>(patientMgr, dbDAOFactory, uuidGeneratorService, timeService);
	}

	std::unique_ptr<IUserModelService> ServicesFactory::buildUserModelService() const
	{
		model::EntityMgr<model::User>& userMgr = m_core.getModel().getUserMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		IUUIDGeneratorService& uuidGeneratorService = m_core.getServicesMgr().getUUIDGeneratorService();
		ITimeService& timeService = m_core.getServicesMgr().getTimeService();

		return std::make_unique<UserModelService>(userMgr, dbDAOFactory, uuidGeneratorService, timeService);
	}


	// Security services
	std::unique_ptr<IAuthorizationValidatorService> ServicesFactory::buildAuthorizationValidatorService() const
	{
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		service::IUserModelService& userModelService = servicesMgr.getUserModelService();
		service::ITimeService& timeService = servicesMgr.getTimeService();
		systelab::jwt::ITokenParserService& jwtTokenParserService = servicesMgr.getJWTTokenParserService();

		return std::make_unique<AuthorizationValidatorService>(userModelService, timeService, jwtTokenParserService);
	}

	std::unique_ptr<systelab::jwt::ITokenBuilderService> ServicesFactory::buildJWTTokenBuilderService() const
	{
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		return std::make_unique<systelab::jwt::TokenBuilderService>(jsonAdapter);
	}

	std::unique_ptr<systelab::jwt::ITokenParserService> ServicesFactory::buildJWTTokenParserService() const
	{
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		return std::make_unique<systelab::jwt::TokenParserService>(jsonAdapter);
	}


	// Validator services
	std::unique_ptr<IJSONValidatorService> ServicesFactory::buildJSONValidatorService() const
	{
		service::IResourceService& resourceService = m_core.getServicesMgr().getResourceService();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<JSONValidatorService>(resourceService, jsonAdapter);
	}


	// System services
	std::unique_ptr<IResourceService> ServicesFactory::buildResourceService() const
	{
		return std::make_unique<ResourceService>();
	}

	std::unique_ptr<ITimeService> ServicesFactory::buildTimeService() const
	{
		return std::make_unique<TimeService>();
	}

	std::unique_ptr<IUUIDGeneratorService> ServicesFactory::buildUUIDGeneratorService() const
	{
		return std::make_unique<UUIDGeneratorService>();
	}

}}
