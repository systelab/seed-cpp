#pragma once

#include <memory>


namespace systelab { namespace rest_api_core {
	class IRouteAccessValidator;
}}

namespace seed_cpp { namespace rest {

	using namespace systelab::rest_api_core;

	class IRouteAccessValidatorsFactory
	{
	public:
		virtual ~IRouteAccessValidatorsFactory() = default;

		virtual std::unique_ptr<IRouteAccessValidator> buildTokenExpirationRouteAccessValidator() const = 0;
		virtual std::unique_ptr<IRouteAccessValidator> buildAdminRoleRouteAccessValidator() const = 0;
		virtual std::unique_ptr<IRouteAccessValidator> buildBasicRoleRouteAccessValidator() const = 0;
	};

}}

