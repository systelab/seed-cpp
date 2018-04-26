#include "StdAfx.h"
#include "ServicesFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/UserModelService.h"
#include "Services/Security/Base64EncodeService.h"
#include "Services/Security/JWTBuilderService.h"
#include "Services/Security/JWTValidatorService.h"
#include "Services/Security/SignatureService.h"


namespace seed_cpp { namespace service {

	ServicesFactory::ServicesFactory(Core& core)
		:m_core(core)
	{
	}
	
	ServicesFactory::~ServicesFactory()
	{
	}

	// Model services
	std::unique_ptr<IUserModelService> ServicesFactory::buildUserModelService() const
	{
		model::EntityMgr<model::User>& userMgr = m_core.getModel().getUserMgr();
		return std::make_unique<UserModelService>(userMgr);
	}


	// Signature services
	std::unique_ptr<IJWTBuilderService> ServicesFactory::buildJWTBuilderService() const
	{
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		IBase64EncodeService& base64EncodeService = servicesMgr.getBase64EncodeService();
		ISignatureService& signatureService = servicesMgr.getSignatureService();

		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<JWTBuilderService>(base64EncodeService, signatureService, jsonAdapter);
	}

	std::unique_ptr<IJWTValidatorService> ServicesFactory::buildJWTValidatorService() const
	{
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		IBase64EncodeService& base64EncodeService = servicesMgr.getBase64EncodeService();
		ISignatureService& signatureService = servicesMgr.getSignatureService();

		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

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

}}
