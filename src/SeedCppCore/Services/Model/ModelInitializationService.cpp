#include "stdafx.h"
#include "ModelInitializationService.h"

#include "Context.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/DAO/ILoadDAO.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "Model/Model.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Model/ModelServicesMgr.h"


namespace seed_cpp { namespace service {

	ModelInitializationService::ModelInitializationService(Context& context)
		:m_context(context)
	{
	}

	ModelInitializationService::~ModelInitializationService() = default;

	void ModelInitializationService::initialize()
	{
		loadUsers();
		loadPatients();
	}

	void ModelInitializationService::loadUsers()
	{
		auto userLoadDAO = m_context.getDbDAOFactory()->buildUserLoadDAO();
		userLoadDAO->loadAll();

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

	void ModelInitializationService::loadPatients()
	{
		std::unique_ptr<dal::ILoadDAO> patientLoadDAO = m_context.getDbDAOFactory()->buildPatientLoadDAO();
		patientLoadDAO->loadAll();
	}

}}
