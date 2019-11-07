#include "stdafx.h"
#include "EndpointsFactory.h"

#include "Context.h"
#include "Model/Model.h"
#include "Model/Patient.h"
#include "Model/UserMgr.h"
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


using namespace systelab::rest_api_core;

namespace seed_cpp { namespace rest {

	EndpointsFactory::EndpointsFactory(Context& context)
		:m_context(context)
	{
	}

	EndpointsFactory::~EndpointsFactory() = default;


	// Health
	std::unique_ptr<IEndpoint> EndpointsFactory::buildHealthGetEndpoint() const
	{
		return std::make_unique<HealthGetEndpoint>();
	}


	// Allergies
	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesGetAllEndpoint() const
	{
		auto& allergyMgr = m_context.getModel()->getAllergyMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<AllergiesGetAllEndpoint>(allergyMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesGetEndpoint() const
	{
		auto& allergyMgr = m_context.getModel()->getAllergyMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<AllergiesGetEndpoint>(allergyMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesPostEndpoint() const
	{
		auto& allergyModelService = m_context.getServicesMgr()->getModelServicesMgr().getAllergyModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<AllergiesPostEndpoint>(jsonTranslatorsFactory, allergyModelService,
													   jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesPutEndpoint() const
	{
		auto& allergyModelService = m_context.getServicesMgr()->getModelServicesMgr().getAllergyModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<AllergiesPutEndpoint>(jsonTranslatorsFactory, allergyModelService,
													  jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildAllergiesDeleteEndpoint() const
	{
		auto& allergyModelService = m_context.getServicesMgr()->getModelServicesMgr().getAllergyModelService();
		return std::make_unique<AllergiesDeleteEndpoint>(allergyModelService);
	}


	// Patients
	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetAllEndpoint() const
	{
		auto& patientMgr = m_context.getModel()->getPatientMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<PatientsGetAllEndpoint>(patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsGetEndpoint() const
	{
		auto& patientMgr = m_context.getModel()->getPatientMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<PatientsGetEndpoint>(patientMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPostEndpoint() const
	{
		auto& patientModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<PatientsPostEndpoint>(jsonTranslatorsFactory, patientModelService,
													  jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsPutEndpoint() const
	{
		auto& patientModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<PatientsPutEndpoint>(jsonTranslatorsFactory, patientModelService,
													 jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildPatientsDeleteEndpoint() const
	{
		auto& patientModelService = m_context.getServicesMgr()->getModelServicesMgr().getPatientModelService();
		return std::make_unique<PatientsDeleteEndpoint>(patientModelService);
	}


	// Users
	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetAllEndpoint() const
	{
		auto& userMgr = m_context.getModel()->getUserMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<UsersGetAllEndpoint>(userMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersGetEndpoint() const
	{
		auto& userMgr = m_context.getModel()->getUserMgr();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<UsersGetEndpoint>(userMgr, jsonTranslatorsFactory, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPostEndpoint() const
	{
		auto& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<UsersPostEndpoint>(jsonTranslatorsFactory, userModelService,
												   jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersPutEndpoint() const
	{
		auto& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		auto& jsonTranslatorsFactory = *m_context.getJSONTranslatorsFactory();
		auto& jsonValidatorService = m_context.getServicesMgr()->getValidatorServicesMgr().getJSONValidatorService();
		auto& jsonAdapter = m_context.getJSONAdapter();

		return std::make_unique<UsersPutEndpoint>(jsonTranslatorsFactory, userModelService,
												  jsonValidatorService, jsonAdapter);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersDeleteEndpoint() const
	{
		auto& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		return std::make_unique<UsersDeleteEndpoint>(userModelService);
	}

	std::unique_ptr<IEndpoint> EndpointsFactory::buildUsersLoginPostEndpoint() const
	{
		service::IUserModelService& userModelService = m_context.getServicesMgr()->getModelServicesMgr().getUserModelService();
		service::ITimeService& timeService = m_context.getServicesMgr()->getSystemServicesMgr().getTimeService();
		systelab::jwt::ITokenBuilderService& jwtBuilderService = m_context.getServicesMgr()->getSecurityServicesMgr().getJWTTokenBuilderService();

		return std::make_unique<UsersLoginPostEndpoint>(userModelService, timeService, jwtBuilderService);
	}

}}
