#include "StdAfx.h"
#include "EndpointsFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Endpoints/Patients/PatientsGetAllEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPostEndpoint.h"


namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Core& core)
		:m_core(core)
	{
	}
	
	EndpointsFactory::~EndpointsFactory()
	{
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientGetAllEndpoint(const EndpointRequestData&)
	{
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<PatientsGetAllEndpoint>(patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientGetEndpoint(const EndpointRequestData& requestData)
	{
		unsigned int patientId = requestData.getRouteParameters()[0].getValue<unsigned int>();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<PatientsGetEndpoint>(patientId, patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientPostEndpoint(const EndpointRequestData& requestData)
	{
		const std::string& requestContent = requestData.getContent();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<PatientsPostEndpoint>(requestContent, patientMgr, dbDAOFactory, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientPutEndpoint(const EndpointRequestData&)
	{
		return std::unique_ptr<IEndpoint>();
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientDeleteEndpoint(const EndpointRequestData&)
	{
		return std::unique_ptr<IEndpoint>();
	}

}}

