#include "stdafx.h"
#include "ValidatorServicesFactory.h"

#include "Context.h"
#include "Services/ServicesMgr.h"
#include "Services/System/SystemServicesMgr.h"
#include "Services/Validator/JSONValidatorService.h"


namespace seed_cpp { namespace service {

	ValidatorServicesFactory::ValidatorServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	ValidatorServicesFactory::~ValidatorServicesFactory() = default;

	std::unique_ptr<IJSONValidatorService> ValidatorServicesFactory::buildJSONValidatorService() const
	{
		service::IResourceService& resourceService = m_context.getServicesMgr()->getSystemServicesMgr().getResourceService();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<JSONValidatorService>(resourceService, jsonAdapter);
	}

}}
