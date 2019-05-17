#include "stdafx.h"
#include "ModelInitializationService.h"

#include "Context.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/DAO/ILoadDAO.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "Model/Model.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/ModelLoaderService.h"
#include "Services/Model/ModelServicesMgr.h"
#include "Services/Model/IUserModelService.h"


namespace seed_cpp { namespace service {

	ModelInitializationService::ModelInitializationService(Context& context)
		:m_context(context)
	{
	}

	ModelInitializationService::~ModelInitializationService() = default;

	void ModelInitializationService::initialize()
	{
		loadModel();
		createDefaultUsers();
	}

	void ModelInitializationService::loadModel()
	{
		ModelLoaderService loader(m_context);
		loader.loadModel();
	}

	void ModelInitializationService::createDefaultUsers()
	{
		model::EntityMgr<model::User>& userMgr = m_context.getModel()->getUserMgr();
		if (userMgr.count() == 0)
		{
			auto defaultUser = std::make_unique<model::User>();
			defaultUser->setSurname("Systelab");
			defaultUser->setName("Systelab");
			defaultUser->setLogin("Systelab");
			defaultUser->setPassword("Systelab");
			defaultUser->setRole(model::User::ADMIN_ROLE);

			auto& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
			model::EntityMgr<model::User>::UniqueLock writeLock(userMgr);
			userModelService.addEntity(std::move(defaultUser), writeLock);
		}
	}

}}
