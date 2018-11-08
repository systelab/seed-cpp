#pragma once

#include "Model/EntityMgr.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace service {

	class IUserModelService
	{
	public:
		virtual ~IUserModelService() {};

		virtual model::EntityMgr<model::User>& getEntityMgr() const = 0;
		virtual const model::User* getEntityById(const std::string& id) const = 0;
		virtual const model::User& addEntity(std::unique_ptr<model::User>) = 0;
		virtual const model::User& editEntity(std::unique_ptr<model::User>) = 0;
		virtual void deleteEntity(const std::string& id) = 0;

		virtual const model::User* getUserByLogin(const std::string&) const = 0;
	};

}}

