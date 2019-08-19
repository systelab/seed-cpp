#include "stdafx.h"
#include "RouteAccessValidatorsFactory.h"

#include "Context.h"
#include "Model/UserRoleNames.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/ModelServicesMgr.h"
#include "Services/System/SystemServicesMgr.h"

#include "RESTAPICore/RouteAccess/TokenExpirationAccessValidator.h"
#include "RESTAPICore/RouteAccess/UserRoleRouteAccessValidator.h"


namespace seed_cpp { namespace rest {

	RouteAccessValidatorsFactory::RouteAccessValidatorsFactory(Context& context)
		:m_context(context)
	{
	}

	RouteAccessValidatorsFactory::~RouteAccessValidatorsFactory() = default;

	std::unique_ptr<IRouteAccessValidator> RouteAccessValidatorsFactory::buildTokenExpirationRouteAccessValidator() const
	{
		long expirationSeconds = 600; // 10 minutes
		auto& epochTimeService = m_context.getServicesMgr()->getSystemServicesMgr().getEpochTimeService();

		return std::make_unique<TokenExpirationAccessValidator>(expirationSeconds, epochTimeService);
	};

	std::unique_ptr<IRouteAccessValidator> RouteAccessValidatorsFactory::buildAdminRoleRouteAccessValidator() const
	{
		auto& roleModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserRoleModelService();
		std::vector<std::string> allowedRoles = { model::user_role::ADMIN_ROLE_NAME };

		return std::make_unique<systelab::rest_api_core::UserRoleRouteAccessValidator>(allowedRoles, roleModelService);
	}

	std::unique_ptr<IRouteAccessValidator> RouteAccessValidatorsFactory::buildBasicRoleRouteAccessValidator() const
	{
		auto& roleModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserRoleModelService();
		std::vector<std::string> allowedRoles = { model::user_role::BASIC_ROLE_NAME };

		return std::make_unique<systelab::rest_api_core::UserRoleRouteAccessValidator>(allowedRoles, roleModelService);
	}

}}

