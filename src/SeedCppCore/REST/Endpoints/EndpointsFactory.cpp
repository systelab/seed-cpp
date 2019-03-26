#include "stdafx.h"
#include "EndpointsFactory.h"

#include "Core.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "Model/UserMgr.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/Patients/PatientsDeleteEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetAllEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPostEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPutEndpoint.h"
#include "REST/Endpoints/Users/UsersDeleteEndpoint.h"
#include "REST/Endpoints/Users/UsersGetAllEndpoint.h"
#include "REST/Endpoints/Users/UsersGetEndpoint.h"
#include "REST/Endpoints/Users/UsersLoginPostEndpoint.h"
#include "REST/Endpoints/Users/UsersPostEndpoint.h"
#include "REST/Endpoints/Users/UsersPutEndpoint.h"
#include "Services/ServicesMgr.h"


namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Core &core)
		:m_core(core)
	{
	}

	EndpointsFactory::~EndpointsFactory() = default;


	// Patients
	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetAllEndpoint(const EndpointRequestData& requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		systelab::web_server::RequestQueryStrings queryStrings = requestData.getQueryStrings();
		model::PatientMgr& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetAllEndpoint>
					(headers, queryStrings, patientMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		model::PatientMgr& patientMgr = m_core.getModel().getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetEndpoint>(headers, patientId, patientMgr,
													 jsonTranslatorsFactory, jsonAdapter,
													 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPostEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		const std::string &requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory &jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter &jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService &authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_core.getServicesMgr().getJSONValidatorService();
		service::IPatientModelService& patientModelService = m_core.getServicesMgr().getPatientModelService();

		return std::make_unique<PatientsPostEndpoint>
					(headers, requestContent, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService, jsonValidatorService, patientModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPutEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		const std::string &requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_core.getServicesMgr().getJSONValidatorService();
		service::IPatientModelService& patientModelService = m_core.getServicesMgr().getPatientModelService();

		return std::make_unique<PatientsPutEndpoint>
					(headers, patientId, requestContent, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService, jsonValidatorService, patientModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsDeleteEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		service::ServicesMgr& servicesMgr = m_core.getServicesMgr();
		service::IPatientModelService& patientModelService = servicesMgr.getPatientModelService();
		service::IAuthorizationValidatorService& authorizationValidatorService = servicesMgr.getAuthorizationValidatorService();

		return std::make_unique<PatientsDeleteEndpoint>
					(headers, patientId, patientModelService, authorizationValidatorService);
	}

	// Users
	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetAllEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		systelab::web_server::RequestQueryStrings queryStrings = requestData.getQueryStrings();
		model::UserMgr& userMgr = m_core.getModel().getUserMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetAllEndpoint>
					(headers, queryStrings, userMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		model::UserMgr& userMgr = m_core.getModel().getUserMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService &authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetEndpoint>
					(headers, userId, userMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPostEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		const std::string& requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService &jsonValidatorService = m_core.getServicesMgr().getJSONValidatorService();
		service::IUserModelService &userModelService = m_core.getServicesMgr().getUserModelService();

		return std::make_unique<UsersPostEndpoint>(
			headers, requestContent, jsonTranslatorsFactory, jsonAdapter,
			authorizationValidatorService, jsonValidatorService, userModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPutEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		const std::string &requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = m_core.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_core.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_core.getServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_core.getServicesMgr().getJSONValidatorService();
		service::IUserModelService& userModelService = m_core.getServicesMgr().getUserModelService();

		return std::make_unique<UsersPutEndpoint>(
			headers, userId, requestContent, jsonTranslatorsFactory, jsonAdapter,
			authorizationValidatorService, jsonValidatorService, userModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersDeleteEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		service::ServicesMgr &servicesMgr = m_core.getServicesMgr();
		service::IUserModelService &userModelService = servicesMgr.getUserModelService();
		service::IAuthorizationValidatorService &authorizationValidatorService =
			servicesMgr.getAuthorizationValidatorService();

		return std::make_unique<UsersDeleteEndpoint>(
			headers, userId, userModelService, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersLoginPostEndpoint(const EndpointRequestData &requestData)
	{
		const std::string& requestContent = requestData.getContent();
		service::IUserModelService& userModelService = m_core.getServicesMgr().getUserModelService();
		service::ITimeService& timeService = m_core.getServicesMgr().getTimeService();
		systelab::jwt::ITokenBuilderService& jwtBuilderService = m_core.getServicesMgr().getJWTTokenBuilderService();

		return std::make_unique<UsersLoginPostEndpoint>(requestContent, userModelService, timeService, jwtBuilderService);
	}

}}
