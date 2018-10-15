#include "StdAfx.h"
#include "EndpointsFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Endpoints/Patients/PatientsDeleteEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetAllEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPostEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPutEndpoint.h"
#include "REST/Endpoints/Users/UsersLoginPostEndpoint.h"
#include "Services/ServicesMgr.h"


namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Core& core)
		:m_core(core)
	{
	}
	
	EndpointsFactory::~EndpointsFactory()
	{
	}


	// Patients
	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetAllEndpoint(const EndpointRequestData&)
	{
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetAllEndpoint>(patientMgr, jsonTranslatorsFactory, jsonAdapter,
														authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetEndpoint(const EndpointRequestData& requestData)
	{
		unsigned int patientId = requestData.getRouteParameters()[0].getValue<unsigned int>();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetEndpoint>(patientId, patientMgr, jsonTranslatorsFactory, jsonAdapter,
													 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPostEndpoint(const EndpointRequestData& requestData)
	{
		const std::string& requestContent = requestData.getContent();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsPostEndpoint>(requestContent, patientMgr, dbDAOFactory, jsonTranslatorsFactory,
													  jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPutEndpoint(const EndpointRequestData& requestData)
	{
		unsigned int patientId = requestData.getRouteParameters()[0].getValue<unsigned int>();
		const std::string& requestContent = requestData.getContent();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json_adapter::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsPutEndpoint>(patientId, requestContent, patientMgr, dbDAOFactory,
													 jsonTranslatorsFactory, jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsDeleteEndpoint(const EndpointRequestData& requestData)
	{
		unsigned int patientId = requestData.getRouteParameters()[0].getValue<unsigned int>();
		model::EntityMgr<model::Patient>& patientMgr = m_core.getModel().getPatientMgr();
		dal::IDbDAOFactory& dbDAOFactory = m_core.getDbDAOFactory();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsDeleteEndpoint>(patientId, patientMgr, dbDAOFactory, authorizationValidatorService);
	}


	// Users
	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersLoginPostEndpoint(const EndpointRequestData& requestData)
	{
		const std::string& requestContent = requestData.getContent();
		service::IUserModelService& userModelService = m_core.getServicesMgr().getUserModelService();
		service::IJWTBuilderService& jwtBuilderService = m_core.getServicesMgr().getJWTBuilderService();
		service::ITimeService& timeService = m_core.getServicesMgr().getTimeService();

		return std::make_unique<UsersLoginPostEndpoint>(requestContent, userModelService,
														jwtBuilderService, timeService);
	}

}}

