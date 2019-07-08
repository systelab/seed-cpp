#include "stdafx.h"
#include "SecurityServicesFactory.h"

#include "Context.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/ModelServicesMgr.h"
#include "Services/Security/AuthorizationValidatorService.h"
#include "Services/Security/SecurityServicesMgr.h"
#include "Services/System/SystemServicesMgr.h"

#include "JWTUtils/Services/TokenBuilderService.h"
#include "JWTUtils/Services/TokenParserService.h"


namespace seed_cpp { namespace service {

	SecurityServicesFactory::SecurityServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	SecurityServicesFactory::~SecurityServicesFactory() = default;

	std::unique_ptr<IAuthorizationValidatorService> SecurityServicesFactory::buildAuthorizationValidatorService() const
	{
		service::ServicesMgr& servicesMgr = *m_context.getServicesMgr();
		service::IUserModelService& userModelService = servicesMgr.getModelServicesMgr().getUserModelService();
		service::ITimeService& timeService = servicesMgr.getSystemServicesMgr().getTimeService();
		systelab::jwt::ITokenParserService& jwtTokenParserService = servicesMgr.getSecurityServicesMgr().getJWTTokenParserService();

		return std::make_unique<AuthorizationValidatorService>(userModelService, timeService, jwtTokenParserService);
	}

	std::unique_ptr<systelab::jwt::ITokenBuilderService> SecurityServicesFactory::buildJWTTokenBuilderService() const
	{
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		return std::make_unique<systelab::jwt::TokenBuilderService>(jsonAdapter);
	}

	std::unique_ptr<systelab::jwt::ITokenParserService> SecurityServicesFactory::buildJWTTokenParserService() const
	{
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		return std::make_unique<systelab::jwt::TokenParserService>(jsonAdapter);
	}

}}
