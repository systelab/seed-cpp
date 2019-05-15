#include "stdafx.h"
#include "ModelServicesMgr.h"

#include "Services/Model/IModelServicesFactory.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Model/IUserModelService.h"


namespace seed_cpp { namespace service {

	ModelServicesMgr::ModelServicesMgr(service::IModelServicesFactory& factory)
		:m_factory(factory)
		,m_patientModelService()
		,m_userModelService()
	{
	}
	
	ModelServicesMgr::~ModelServicesMgr() = default;

	IPatientModelService& ModelServicesMgr::getPatientModelService() const
	{
		if (!m_patientModelService.get())
		{
			m_patientModelService = m_factory.buildPatientModelService();
		}

		return *m_patientModelService;
	}

	IUserModelService& ModelServicesMgr::getUserModelService() const
	{
		if (!m_userModelService.get())
		{
			m_userModelService = m_factory.buildUserModelService();
		}

		return *m_userModelService;
	}

}}

