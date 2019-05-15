#include "stdafx.h"
#include "ModelServicesFactory.h"

#include "Context.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/PatientModelService.h"
#include "Services/Model/UserModelService.h"
#include "Services/System/SystemServicesMgr.h"


namespace seed_cpp { namespace service {

	ModelServicesFactory::ModelServicesFactory(Context& context)
		:m_context(context)
	{
	}
	
	ModelServicesFactory::~ModelServicesFactory() = default;

	std::unique_ptr<IPatientModelService> ModelServicesFactory::buildPatientModelService() const
	{
		auto& patientMgr = m_context.getModel()->getPatientMgr();
		auto& dbDAOFactory = *m_context.getDbDAOFactory();
		auto& systemServicesMgr = m_context.getServicesMgr()->getSystemServicesMgr();
		auto& uuidGeneratorService = systemServicesMgr.getUUIDGeneratorService();
		auto& timeService = systemServicesMgr.getTimeService();

		return std::make_unique<PatientModelService>(patientMgr, dbDAOFactory, uuidGeneratorService, timeService);
	}

	std::unique_ptr<IUserModelService> ModelServicesFactory::buildUserModelService() const
	{
		auto& userMgr = m_context.getModel()->getUserMgr();
		auto& dbDAOFactory = *m_context.getDbDAOFactory();
		auto& systemServicesMgr = m_context.getServicesMgr()->getSystemServicesMgr();
		auto& uuidGeneratorService = systemServicesMgr.getUUIDGeneratorService();
		auto& timeService = systemServicesMgr.getTimeService();

		return std::make_unique<UserModelService>(userMgr, dbDAOFactory, uuidGeneratorService, timeService);
	}

}}
