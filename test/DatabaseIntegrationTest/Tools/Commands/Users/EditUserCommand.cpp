#include "stdafx.h"
#include "EditUserCommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"

#include "SeedCppCore/Model/User.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelServicesMgr.h"
#include "SeedCppCore/Services/Model/IUserModelService.h"


namespace seed_cpp { namespace db_test {

	EditUserCommand::EditUserCommand(const model::User& user)
		:m_user(std::make_unique<model::User>(user))
	{
	}

	EditUserCommand::~EditUserCommand() = default;

	void EditUserCommand::execute(Core& core)
	{
		auto& service = core.getServicesMgr().getModelServicesMgr().getUserModelService();
		model::EntityMgr<model::User>::UniqueLock lock(service.getEntityMgr());
		service.editEntity(std::move(m_user), lock);
	}

}}
