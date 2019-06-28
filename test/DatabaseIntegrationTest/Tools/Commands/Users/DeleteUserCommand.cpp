#include "stdafx.h"
#include "DeleteUserCommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"

#include "SeedCppCore/Model/UserMgr.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelServicesMgr.h"
#include "SeedCppCore/Services/Model/IUserModelService.h"


namespace seed_cpp { namespace db_test {

	DeleteUserCommand::DeleteUserCommand(const std::string& userId)
		:m_userId(userId)
	{
	}

	DeleteUserCommand::~DeleteUserCommand() = default;

	void DeleteUserCommand::execute(Core& core)
	{
		auto& service = core.getServicesMgr().getModelServicesMgr().getUserModelService();
		model::UserMgr::UniqueLock lock(service.getEntityMgr());
		service.deleteEntity(m_userId, lock);
	}

	std::unique_ptr<ICommand> DeleteUserCommand::clone()
	{
		return std::make_unique<DeleteUserCommand>(m_userId);
	}

}}

