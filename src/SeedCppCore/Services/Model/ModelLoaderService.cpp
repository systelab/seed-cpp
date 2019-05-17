#include "stdafx.h"
#include "ModelLoaderService.h"

#include "Context.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/DAO/ILoadDAO.h"
#include "Model/Model.h"


namespace seed_cpp { namespace service {

	ModelLoaderService::ModelLoaderService(Context& context)
		:m_context(context)
	{
	}

	ModelLoaderService::~ModelLoaderService() = default;

	void ModelLoaderService::loadModel()
	{
		loadUsers();
		loadPatients();
	}

	void ModelLoaderService::loadUsers()
	{
		auto userLoadDAO = m_context.getDbDAOFactory()->buildUserLoadDAO();
		userLoadDAO->loadAll();
	}

	void ModelLoaderService::loadPatients()
	{
		std::unique_ptr<dal::ILoadDAO> patientLoadDAO = m_context.getDbDAOFactory()->buildPatientLoadDAO();
		patientLoadDAO->loadAll();
	}

}}
