#include "StdAfx.h"
#include "PatientsDeleteEndpoint.h"

#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/DAO/ISaveDAO.h"
#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "WebServerInterface/Model/Reply.h"
#include "WebServerInterface/Model/RequestHeaders.h"


namespace seed_cpp { namespace rest {

	PatientsDeleteEndpoint::PatientsDeleteEndpoint(const systelab::web_server::RequestHeaders& headers,
												   unsigned int id,
												   model::EntityMgr<model::Patient>& patientMgr,
												   dal::IDbDAOFactory& dbDAOFactory,
												   service::IAuthorizationValidatorService& authorizationValidatorService)
		:m_headers(headers)
		,m_id(id)
		,m_patientMgr(patientMgr)
		,m_dbDAOFactory(dbDAOFactory)
		,m_authorizationValidatorService(authorizationValidatorService)
	{
	}
	
	PatientsDeleteEndpoint::~PatientsDeleteEndpoint()
	{
	}

	bool PatientsDeleteEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> PatientsDeleteEndpoint::execute()
	{
		const model::Patient* existingPatient = m_patientMgr.getEntityById(m_id);
		if (!existingPatient)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
		}

		try
		{
			auto patientToDelete = std::make_unique<model::Patient>(*existingPatient);
			auto patientSaveDAO = m_dbDAOFactory.buildPatientSaveDAO(*patientToDelete);
			patientSaveDAO->deleteEntity();
			m_patientMgr.deleteEntity(m_id);

			return ReplyBuilderHelper::build(systelab::web_server::Reply::NO_CONTENT);
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

