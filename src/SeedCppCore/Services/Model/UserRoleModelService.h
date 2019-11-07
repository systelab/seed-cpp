#pragma once

#include "RESTAPICore/RouteAccess/IUserRoleService.h"

#include "Model/User.h"
#include "Model/UserMgr.h"
#include "Services/Model/EntityModelService.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class IUserModelService;

	class UserRoleModelService : public systelab::rest_api_core::IUserRoleService
	{
	public:
		UserRoleModelService(service::IUserModelService&);
		virtual ~UserRoleModelService();

		std::vector<std::string> getUserRoles(const std::string& username) const override;

	private:
		service::IUserModelService& m_userModelService;
	};

}}

