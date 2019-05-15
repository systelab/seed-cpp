#include "stdafx.h"
#include "ServicesMgr.h"

#include "Context.h"
#include "Services/Model/ModelServicesMgr.h"
#include "Services/Security/SecurityServicesMgr.h"
#include "Services/System/SystemServicesMgr.h"
#include "Services/Validator/ValidatorServicesMgr.h"


namespace seed_cpp { namespace service {

	ServicesMgr::ServicesMgr(Context& context)
		:m_context(context)
		,m_modelServicesMgr()
		,m_securityServicesMgr()
		,m_systemServicesMgr()
		,m_validatorServicesMgr()
	{
	}
	
	ServicesMgr::~ServicesMgr() = default;

	ModelServicesMgr& ServicesMgr::getModelServicesMgr() const
	{
		if (!m_modelServicesMgr.get())
		{
			auto& factory = *m_context.getModelServicesFactory();
			m_modelServicesMgr = std::make_unique<ModelServicesMgr>(factory);
		}

		return *m_modelServicesMgr;
	}

	SecurityServicesMgr& ServicesMgr::getSecurityServicesMgr() const
	{
		if (!m_securityServicesMgr.get())
		{
			auto& factory = *m_context.getSecurityServicesFactory();
			m_securityServicesMgr = std::make_unique<SecurityServicesMgr>(factory);
		}

		return *m_securityServicesMgr;
	}

	SystemServicesMgr& ServicesMgr::getSystemServicesMgr() const
	{
		if (!m_systemServicesMgr.get())
		{
			auto& factory = *m_context.getSystemServicesFactory();
			m_systemServicesMgr = std::make_unique<SystemServicesMgr>(factory);
		}

		return *m_systemServicesMgr;
	}

	ValidatorServicesMgr& ServicesMgr::getValidatorServicesMgr() const
	{
		if (!m_validatorServicesMgr.get())
		{
			auto& factory = *m_context.getValidatorServicesFactory();
			m_validatorServicesMgr = std::make_unique<ValidatorServicesMgr>(factory);
		}

		return *m_validatorServicesMgr;
	}

}}

