#include "stdafx.h"
#include "IDbDAOFactory.h"

#include "DAL/DAO/ILoadDAO.h"
#include "DAL/DAO/ISaveDAO.h"
#include "Model/EntityMgr.h"
#include "Model/Patient.h"
#include "Model/User.h"


namespace seed_cpp { namespace dal {

	//ISaveDAO
	template<>
	std::unique_ptr<ISaveDAO> IDbDAOFactory::buildEntitySaveDAO(model::Patient& entity)
	{
		return buildPatientSaveDAO(entity);
	}

	template<>
	std::unique_ptr<ISaveDAO> IDbDAOFactory::buildEntitySaveDAO(model::User& entity)
	{
		return buildUserSaveDAO(entity);
	}

}}
