#include "StdAfx.h"
#include "ServicesMgr.h"

#include "Services/IServicesFactory.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IBase64EncodeService.h"
#include "Services/Security/ISignatureService.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(service::IServicesFactory& factory)
		:m_servicesFactory(factory)
		,m_userModelService()
		,m_signatureService()
		,m_base64EncodeService()
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

}}

