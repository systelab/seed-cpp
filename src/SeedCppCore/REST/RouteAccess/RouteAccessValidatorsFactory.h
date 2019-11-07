#pragma once

#include "IRouteAccessValidatorsFactory.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace rest {

	using namespace systelab::rest_api_core;

	class RouteAccessValidatorsFactory : public IRouteAccessValidatorsFactory
	{
	public:
		RouteAccessValidatorsFactory(Context&);
		virtual ~RouteAccessValidatorsFactory();

		std::unique_ptr<IRouteAccessValidator> buildTokenExpirationRouteAccessValidator() const override;
		std::unique_ptr<IRouteAccessValidator> buildAdminRoleRouteAccessValidator() const override;
		std::unique_ptr<IRouteAccessValidator> buildBasicRoleRouteAccessValidator() const override;

	private:
		Context& m_context;
	};

}}

