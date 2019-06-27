#pragma once

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

		IAllergyModelService& getAllergyModelService() const;
		IPatientModelService& getPatientModelService() const;
		IUserModelService& getUserModelService() const;

	private:
		IModelServicesFactory& m_factory;

		mutable std::unique_ptr<IAllergyModelService> m_allergyModelService;
		mutable std::unique_ptr<IPatientModelService> m_patientModelService;
		mutable std::unique_ptr<IUserModelService> m_userModelService;
	};

}}

