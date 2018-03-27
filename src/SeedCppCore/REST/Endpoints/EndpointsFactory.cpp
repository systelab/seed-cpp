#include "StdAfx.h"
#include "EndpointsFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetAllEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetEndpoint.h"


namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Core& core)
		:m_core(core)
	{
	}
	
	EndpointsFactory::~EndpointsFactory()
	{
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientGETAllEndpoint(const std::vector<RouteParam>&)
	{
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<PatientsGetAllEndpoint>(patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientGETEndpoint(const std::vector<RouteParam>& params)
	{
		unsigned int patientId = params[0].getValue<unsigned int>();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();

		return std::make_unique<PatientsGetEndpoint>(patientId, patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientPOSTEndpoint(const std::vector<RouteParam>&)
	{
		return std::unique_ptr<IEndpoint>();
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientPUTEndpoint(const std::vector<RouteParam>&)
	{
		return std::unique_ptr<IEndpoint>();
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientDELETEEndpoint(const std::vector<RouteParam>&)
	{
		return std::unique_ptr<IEndpoint>();
	}

}}

