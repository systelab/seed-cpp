#include "StdAfx.h"
#include "ServicesFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/UserModelService.h"
#include "Services/Security/Base64EncodeService.h"
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
		return std::unique_ptr<IUserModelService>(new UserModelService(userMgr));
	}


	// Signature services
	std::unique_ptr<ISignatureService> ServicesFactory::buildSignatureService() const
	{
		IBase64EncodeService& base64EncodeService = m_core.getServicesMgr().getBase64EncodeService();
		return std::unique_ptr<ISignatureService>(new SignatureService(base64EncodeService));
	}

	std::unique_ptr<IBase64EncodeService> ServicesFactory::buildBase64EncodeService() const
	{
		return std::unique_ptr<IBase64EncodeService>(new Base64EncodeService());
	}

}}
