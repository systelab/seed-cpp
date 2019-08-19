#include "stdafx.h"
#include "UserRoleModelService.h"

#include "Model/User.h"
#include "Services/Model/IUserModelService.h"


namespace seed_cpp { namespace service {

	UserRoleModelService::UserRoleModelService(service::IUserModelService& userModelService)
		:m_userModelService(userModelService)
	{
	}

	UserRoleModelService::~UserRoleModelService() = default;

	std::vector<std::string> UserRoleModelService::getUserRoles(const std::string& username) const
	{
		auto readLock = m_userModelService.createReadLock();
		const model::User* user = m_userModelService.getUserByLogin(username, *readLock);
		if (!user)
		{
			return {};
		}

		model::User::Role userRole = user->getRole();
		switch (userRole)
		{
			case model::User::ADMIN_ROLE:
				return { "Admin", "Basic" };
			case model::User::BASIC_ROLE:
				return { "Basic" };
			default:
				return {};
		}
	}

}}

