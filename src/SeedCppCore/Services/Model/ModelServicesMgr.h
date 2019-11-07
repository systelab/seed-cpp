#pragma once

namespace systelab { namespace rest_api_core {
	class IUserRoleService;
}}

namespace seed_cpp { namespace service {

	class IModelServicesFactory;

	class IAllergyModelService;
	class IPatientModelService;
	class IUserModelService;

	class ModelServicesMgr
	{
	public:
		ModelServicesMgr(service::IModelServicesFactory&);
		virtual ~ModelServicesMgr();

		// Model entity services
		IAllergyModelService& getAllergyModelService() const;
		IPatientModelService& getPatientModelService() const;
		IUserModelService& getUserModelService() const;

		// Login services
		systelab::rest_api_core::IUserRoleService& getUserRoleModelService() const;

	private:
		IModelServicesFactory& m_factory;

		mutable std::unique_ptr<IAllergyModelService> m_allergyModelService;
		mutable std::unique_ptr<IPatientModelService> m_patientModelService;
		mutable std::unique_ptr<IUserModelService> m_userModelService;

		mutable std::unique_ptr<systelab::rest_api_core::IUserRoleService> m_userRoleModelService;
	};

}}

