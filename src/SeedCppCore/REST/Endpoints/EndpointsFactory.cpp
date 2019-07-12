#include "stdafx.h"
#include "EndpointsFactory.h"

#include "Context.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "Model/UserMgr.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/Allergies/AllergiesDeleteEndpoint.h"
#include "REST/Endpoints/Allergies/AllergiesGetEndpoint.h"
#include "REST/Endpoints/Allergies/AllergiesGetAllEndpoint.h"
#include "REST/Endpoints/Allergies/AllergiesPostEndpoint.h"
#include "REST/Endpoints/Allergies/AllergiesPutEndpoint.h"
#include "REST/Endpoints/Health/HealthGetEndpoint.h"
#include "REST/Endpoints/Patients/PatientsDeleteEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetEndpoint.h"
#include "REST/Endpoints/Patients/PatientsGetAllEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPostEndpoint.h"
#include "REST/Endpoints/Patients/PatientsPutEndpoint.h"
#include "REST/Endpoints/Users/UsersDeleteEndpoint.h"
#include "REST/Endpoints/Users/UsersGetEndpoint.h"
#include "REST/Endpoints/Users/UsersGetAllEndpoint.h"
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

	// Allergies
	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesGetAllEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& queryStrings = requestData.getQueryStrings();
		auto& entityMgr = m_context.getModel()->getAllergyMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<AllergiesGetAllEndpoint>(headers, queryStrings, entityMgr,
														std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
														jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesGetEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& entityMgr = m_context.getModel()->getAllergyMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& securityServicesMgr = m_context.getServicesMgr()->getSecurityServicesMgr();
		auto& authorizationValidatorService = securityServicesMgr.getAuthorizationValidatorService();

		return std::make_unique<AllergiesGetEndpoint>(headers, entityId, entityMgr,
												  std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												  jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesPostEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_ALLERGIES_POST";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getAllergyModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& securityServicesMgr = m_context.getServicesMgr()->getSecurityServicesMgr();
		auto& authorizationValidatorService = securityServicesMgr.getAuthorizationValidatorService();
		auto& validatorServicesMgr = m_context.getServicesMgr()->getValidatorServicesMgr();
		auto& jsonValidatorService = validatorServicesMgr.getJSONValidatorService();

		return std::make_unique<AllergiesPostEndpoint>(headers, requestContent, schema, entityModelService,
													   std::bind(&dal::IJSONTranslatorsFactory::buildAllergyLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													   std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													   jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesPutEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_ALLERGIES_PUT";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getAllergyModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();

		return std::make_unique<AllergiesPutEndpoint>(headers, entityId, requestContent, schema, entityModelService,
													  std::bind(&dal::IJSONTranslatorsFactory::buildAllergyLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													  std::bind(&dal::IJSONTranslatorsFactory::buildAllergySaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													  jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesDeleteEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& servicesMgr = *m_context.getServicesMgr();
		auto& entityModelService = servicesMgr.getModelServicesMgr().getAllergyModelService();
		auto& authorizationValidatorService = servicesMgr.getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<AllergiesDeleteEndpoint>(headers, entityId, entityModelService, authorizationValidatorService);
	}


	// Health
	std::unique_ptr<IEndpoint> EndpointsFactory::buildHealthGetEndpoint(const EndpointRequestData&)
	{
		return std::make_unique<HealthGetEndpoint>();
	}


	// Patients
	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetAllEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& queryStrings = requestData.getQueryStrings();
		auto& entityMgr = m_context.getModel()->getPatientMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetAllEndpoint>(headers, queryStrings, entityMgr,
														std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
														jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& entityMgr = m_context.getModel()->getPatientMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsGetEndpoint>(headers, entityId, entityMgr,
													 std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													 jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPostEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_PATIENTS_POST";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();

		return std::make_unique<PatientsPostEndpoint>(headers, requestContent, schema, entityModelService,
													  std::bind(&dal::IJSONTranslatorsFactory::buildPatientLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													  std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													  jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPutEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_PATIENTS_PUT";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();

		return std::make_unique<PatientsPutEndpoint>(headers, entityId, requestContent, schema, entityModelService,
													 std::bind(&dal::IJSONTranslatorsFactory::buildPatientLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													 std::bind(&dal::IJSONTranslatorsFactory::buildPatientSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													 jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsDeleteEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& servicesMgr = *m_context.getServicesMgr();
		auto& entityModelService = servicesMgr.getModelServicesMgr().getPatientModelService();
		auto& authorizationValidatorService = servicesMgr.getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<PatientsDeleteEndpoint>(headers, entityId, entityModelService, authorizationValidatorService);
	}

	// Users
	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetAllEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& queryStrings = requestData.getQueryStrings();
		auto& entityMgr = m_context.getModel()->getUserMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetAllEndpoint>(headers, queryStrings, entityMgr,
													 std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
													 jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& entityMgr = m_context.getModel()->getUserMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersGetEndpoint>(headers, entityId, entityMgr,
												  std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												  jsonAdapter, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPostEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_USERS_POST";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();

		return std::make_unique<UsersPostEndpoint>(headers, requestContent, schema, entityModelService,
												   std::bind(&dal::IJSONTranslatorsFactory::buildUserLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												   std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												   jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPutEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		const auto& requestContent = requestData.getContent();
		std::string schema = "JSON_SCHEMA_ENDPOINT_USERS_PUT";
		auto& entityModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();
		auto& authorizationValidatorService = m_context.getServicesMgr()->getSecurityServicesMgr().getAuthorizationValidatorService();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();

		return std::make_unique<UsersPutEndpoint>(headers, entityId, requestContent, schema, entityModelService,
												  std::bind(&dal::IJSONTranslatorsFactory::buildUserLoadTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												  std::bind(&dal::IJSONTranslatorsFactory::buildUserSaveTranslator, &jsonTranslatorsFactory, std::placeholders::_1),
												  jsonAdapter, authorizationValidatorService, jsonValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersDeleteEndpoint(const EndpointRequestData& requestData)
	{
		const auto& headers = requestData.getHeaders();
		auto entityId = requestData.getRouteParameters()[0].getValue<std::string>();
		auto& servicesMgr = *m_context.getServicesMgr();
		auto& entityModelService = servicesMgr.getModelServicesMgr().getUserModelService();
		auto& authorizationValidatorService = servicesMgr.getSecurityServicesMgr().getAuthorizationValidatorService();

		return std::make_unique<UsersDeleteEndpoint>(headers, entityId, entityModelService, authorizationValidatorService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersLoginPostEndpoint(const EndpointRequestData& requestData)
	{
		const std::string& requestContent = requestData.getContent();
		service::IUserModelService& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		service::ITimeService& timeService = m_context.getServicesMgr()->getSystemServicesMgr().getTimeService();
		systelab::jwt::ITokenBuilderService& jwtBuilderService = m_context.getServicesMgr()->getSecurityServicesMgr().getJWTTokenBuilderService();

		return std::make_unique<UsersLoginPostEndpoint>(requestContent, userModelService, timeService, jwtBuilderService);
	}

}}
