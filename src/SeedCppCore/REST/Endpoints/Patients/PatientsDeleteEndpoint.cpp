#include "StdAfx.h"
#include "PatientsDeleteEndpoint.h"

#include "Model/Patient.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Model/IPatientModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "WebServerInterface/Model/Reply.h"
#include "WebServerInterface/Model/RequestHeaders.h"


namespace seed_cpp { namespace rest {

	PatientsDeleteEndpoint::PatientsDeleteEndpoint(const systelab::web_server::RequestHeaders& headers,
												   const std::string& id,
												   service::IPatientModelService& patientModelService,
												   service::IAuthorizationValidatorService& authorizationValidatorService)
		:m_headers(headers)
		,m_id(id)
		,m_patientModelService(patientModelService)
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
		model::EntityMgr<model::Patient>::UniqueLock writeLock(m_patientModelService.getEntityMgr());
		const model::Patient* existingPatient = m_patientModelService.getEntityById(m_id, writeLock);
		if (!existingPatient)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
		}

		try
		{
			m_patientModelService.deleteEntity(m_id, writeLock);
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NO_CONTENT);
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

