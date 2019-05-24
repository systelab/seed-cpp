#include "stdafx.h"
#include "AddUserCommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelServicesMgr.h"
#include "SeedCppCore/Services/Model/IUserModelService.h"


namespace seed_cpp { namespace db_test {

	AddUserCommand::AddUserCommand(const model::User& user)
		:m_user(std::make_unique<model::User>(user))
	{
	}

	AddUserCommand::~AddUserCommand() = default;

	void AddUserCommand::execute(Core& core)
	{
		auto& service = core.getServicesMgr().getModelServicesMgr().getUserModelService();
		model::EntityMgr<model::User>::UniqueLock lock(service.getEntityMgr());
		service.addEntity(std::move(m_user), lock);
	}

	std::unique_ptr<ICommand> AddUserCommand::clone()
	{
		return std::make_unique<AddUserCommand>(*m_user);
	}

}}
