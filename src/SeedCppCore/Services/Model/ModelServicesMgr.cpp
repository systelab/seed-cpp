#include "stdafx.h"
#include "ModelServicesMgr.h"

#include "Services/Model/IAllergyModelService.h"
#include "Services/Model/IModelServicesFactory.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Model/IUserModelService.h"


namespace seed_cpp { namespace service {

	ModelServicesMgr::ModelServicesMgr(service::IModelServicesFactory& factory)
		:m_factory(factory)
	{
	}
	
	ModelServicesMgr::~ModelServicesMgr() = default;

	IAllergyModelService& ModelServicesMgr::getAllergyModelService() const
	{
		if (!m_allergyModelService)
		{
			m_allergyModelService = m_factory.buildAllergyModelService();
		}

		return *m_allergyModelService;
	}

	IPatientModelService& ModelServicesMgr::getPatientModelService() const
	{
		if (!m_patientModelService)
		{
			m_patientModelService = m_factory.buildPatientModelService();
		}

		return *m_patientModelService;
	}

	IUserModelService& ModelServicesMgr::getUserModelService() const
	{
		if (!m_userModelService)
		{
			m_userModelService = m_factory.buildUserModelService();
		}

		return *m_userModelService;
	}

}}

