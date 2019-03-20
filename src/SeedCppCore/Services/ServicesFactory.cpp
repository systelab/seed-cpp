#include "stdafx.h"
#include "ServicesFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/PatientModelService.h"
#include "Services/Model/UserModelService.h"
#include "Services/Security/AuthorizationValidatorService.h"
#include "Services/Security/Base64EncodeService.h"
#include "Services/Security/JWTBuilderService.h"
#include "Services/Security/JWTValidatorService.h"
#include "Services/Security/SignatureService.h"
#include "Services/System/ResourceService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"
#include "Services/Validator/JSONValidatorService.h"


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
		IJWTValidatorService& jwtValidatorService = servicesMgr.getJWTValidatorService();
		IUserModelService& userModelService = servicesMgr.getUserModelService();
		ITimeService& timeService = servicesMgr.getTimeService();

		return std::make_unique<AuthorizationValidatorService>(jwtValidatorService, userModelService, timeService);
	}

	std::unique_ptr<IJWTBuilderService> ServicesFactory::buildJWTBuilderService() const
	{
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		IBase64EncodeService& base64EncodeService = servicesMgr.getBase64EncodeService();
		ISignatureService& signatureService = servicesMgr.getSignatureService();

		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<JWTBuilderService>(base64EncodeService, signatureService, jsonAdapter);
	}

	std::unique_ptr<IJWTValidatorService> ServicesFactory::buildJWTValidatorService() const
	{
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		IBase64EncodeService& base64EncodeService = servicesMgr.getBase64EncodeService();
		ISignatureService& signatureService = servicesMgr.getSignatureService();

		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<JWTValidatorService>(base64EncodeService, signatureService, jsonAdapter);
	}

	std::unique_ptr<ISignatureService> ServicesFactory::buildSignatureService() const
	{
		IBase64EncodeService& base64EncodeService = m_core.getServicesMgr().getBase64EncodeService();
		return std::make_unique<SignatureService>(base64EncodeService);
	}

	std::unique_ptr<IBase64EncodeService> ServicesFactory::buildBase64EncodeService() const
	{
		return std::make_unique<Base64EncodeService>();
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
