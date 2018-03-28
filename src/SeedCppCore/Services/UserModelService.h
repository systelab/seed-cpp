#pragma once

#include "IUserModelService.h"
#include "Model/EntityMgr.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class UserModelService : public IUserModelService
	{
	public:
		UserModelService(model::EntityMgr<model::User>&);
		virtual ~UserModelService();

		const model::User* getUserByLogin(const std::string&) const;

	private:
		model::EntityMgr<model::User>& m_userMgr;
	};

}}

