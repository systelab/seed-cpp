#include "stdafx.h"
#include "EndpointsFactory.h"

#include "Context.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/Health/HealthGetEndpoint.h"
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
#include "Services/Model/ModelServicesMgr.h"
#include "Services/Security/SecurityServicesMgr.h"
#include "Services/System/SystemServicesMgr.h"
#include "Services/Validator/ValidatorServicesMgr.h"


namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Context& context)
		:m_context(context)
	{
	}

	EndpointsFactory::~EndpointsFactory() = default;


	// Health
	std::unique_ptr<IEndpoint> EndpointsFactory::buildHealthGetEndpoint(const EndpointRequestData&)
	{
		return std::make_unique<HealthGetEndpoint>();
	}


	// Patients
	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetAllEndpoint(const EndpointRequestData& requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		systelab::web_server::RequestQueryStrings queryStrings = requestData.getQueryStrings();
		model::EntityMgr<model::Patient>& patientMgr = m_context.getModel()->getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetAllEndpoint>
					(headers, queryStrings, patientMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		model::EntityMgr<model::Patient>& patientMgr = m_context.getModel()->getPatientMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetEndpoint>(headers, patientId, patientMgr,
													 jsonTranslatorsFactory, jsonAdapter,
													 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPostEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		const std::string& requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		service::IPatientModelService& patientModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();

		return std::make_unique<PatientsPostEndpoint>
					(headers, requestContent, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService, jsonValidatorService, patientModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPutEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		const std::string &requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		service::IPatientModelService& patientModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();

		return std::make_unique<PatientsPutEndpoint>
					(headers, patientId, requestContent, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService, jsonValidatorService, patientModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsDeleteEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string patientId = requestData.getRouteParameters()[0].getValue<std::string>();
		service::ServicesMgr& servicesMgr = *m_context.getServicesMgr();
		service::IPatientModelService& patientModelService = servicesMgr.getModelServicesMgr().getPatientModelService();
		service::IAuthorizationValidatorService& authorizationValidatorService = servicesMgr.getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsDeleteEndpoint>
					(headers, patientId, patientModelService, authorizationValidatorService);
	}

	// Users
	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetAllEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		systelab::web_server::RequestQueryStrings queryStrings = requestData.getQueryStrings();
		model::EntityMgr<model::User>& userMgr = m_context.getModel()->getUserMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetAllEndpoint>
					(headers, queryStrings, userMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		model::EntityMgr<model::User>& userMgr = m_context.getModel()->getUserMgr();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService &authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetEndpoint>
					(headers, userId, userMgr, jsonTranslatorsFactory, jsonAdapter,
					 authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPostEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		const std::string& requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService &jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		service::IUserModelService &userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();

		return std::make_unique<UsersPostEndpoint>(
			headers, requestContent, jsonTranslatorsFactory, jsonAdapter,
			authorizationValidatorService, jsonValidatorService, userModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPutEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		const std::string &requestContent = requestData.getContent();
		dal::IJSONTranslatorsFactory& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		systelab::json::IJSONAdapter& jsonAdapter = m_context.getJSONAdapter();
		service::IAuthorizationValidatorService& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		service::IJSONValidatorService& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		service::IUserModelService& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();

		return std::make_unique<UsersPutEndpoint>(
			headers, userId, requestContent, jsonTranslatorsFactory, jsonAdapter,
			authorizationValidatorService, jsonValidatorService, userModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersDeleteEndpoint(const EndpointRequestData &requestData)
	{
		systelab::web_server::RequestHeaders headers = requestData.getHeaders();
		std::string userId = requestData.getRouteParameters()[0].getValue<std::string>();
		service::ServicesMgr &servicesMgr = *m_context.getServicesMgr();
		service::IUserModelService &userModelService = servicesMgr.getModelServicesMgr().getUserModelService();
		service::IAuthorizationValidatorService &authorizationValidatorService = servicesMgr.getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersDeleteEndpoint>(headers, userId, userModelService, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersLoginPostEndpoint(const EndpointRequestData &requestData)
	{
		const std::string& requestContent = requestData.getContent();
		service::IUserModelService& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		service::ITimeService& timeService = m_context.getServicesMgr()->getSystemServicesMgr().getTimeService();
		systelab::jwt::ITokenBuilderService& jwtBuilderService = m_context.getServicesMgr()->getSecurityServicesMgr().getJWTTokenBuilderService();

		return std::make_unique<UsersLoginPostEndpoint>(requestContent, userModelService, timeService, jwtBuilderService);
	}

}}
