#include "stdafx.h"
#include "SecurityServicesFactory.h"

#include "Context.h"

#include "JWTUtils/Services/TokenBuilderService.h"
#include "JWTUtils/Services/TokenParserService.h"


namespace seed_cpp { namespace service {

	SecurityServicesFactory::SecurityServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	SecurityServicesFactory::~SecurityServicesFactory() = default;

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
