#include "stdafx.h"
#include "ModelServicesFactory.h"

#include "Context.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/AllergyModelService.h"
#include "Services/Model/ModelServicesMgr.h"
#include "Services/Model/PatientModelService.h"
#include "Services/Model/UserModelService.h"
#include "Services/Model/UserRoleModelService.h"
#include "Services/System/SystemServicesMgr.h"


namespace seed_cpp { namespace service {

	ModelServicesFactory::ModelServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	ModelServicesFactory::~ModelServicesFactory() = default;


	// Model entity services
	std::unique_ptr<IAllergyModelService> ModelServicesFactory::buildAllergyModelService() const
	{
		auto& entityMgr = m_context.getModel()->getAllergyMgr();
		auto& dbDAOFactory = *m_context.getDbDAOFactory();
		auto& systemServicesMgr = m_context.getServicesMgr()->getSystemServicesMgr();
		auto& uuidGeneratorService = systemServicesMgr.getUUIDGeneratorService();
		auto& timeService = systemServicesMgr.getTimeService();

		return std::make_unique<AllergyModelService>
					(entityMgr, dbDAOFactory, std::bind(&dal::IDbDAOFactory::buildAllergySaveDAO, &dbDAOFactory, std::placeholders::_1),
					 uuidGeneratorService, timeService);
	}

	std::unique_ptr<IPatientModelService> ModelServicesFactory::buildPatientModelService() const
	{
		auto& patientMgr = m_context.getModel()->getPatientMgr();
		auto& dbDAOFactory = *m_context.getDbDAOFactory();
		auto& systemServicesMgr = m_context.getServicesMgr()->getSystemServicesMgr();
		auto& uuidGeneratorService = systemServicesMgr.getUUIDGeneratorService();
		auto& timeService = systemServicesMgr.getTimeService();

		return std::make_unique<PatientModelService>(patientMgr, dbDAOFactory, std::bind(&dal::IDbDAOFactory::buildPatientSaveDAO, &dbDAOFactory, std::placeholders::_1),
													 uuidGeneratorService, timeService);
	}

	std::unique_ptr<IUserModelService> ModelServicesFactory::buildUserModelService() const
	{
		auto& userMgr = m_context.getModel()->getUserMgr();
		auto& dbDAOFactory = *m_context.getDbDAOFactory();
		auto& systemServicesMgr = m_context.getServicesMgr()->getSystemServicesMgr();
		auto& uuidGeneratorService = systemServicesMgr.getUUIDGeneratorService();
		auto& timeService = systemServicesMgr.getTimeService();

		return std::make_unique<UserModelService>(userMgr, dbDAOFactory, std::bind(&dal::IDbDAOFactory::buildUserSaveDAO, &dbDAOFactory, std::placeholders::_1),
												  uuidGeneratorService, timeService);
	}


	// Login services
	std::unique_ptr<systelab::rest_api_core::IUserRoleService > ModelServicesFactory::buildUserRoleModelService() const
	{
		auto& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		return std::make_unique<UserRoleModelService>(userModelService);
	}

}}
