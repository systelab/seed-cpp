#pragma once

namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class ModelServicesMgr;
	class SecurityServicesMgr;
	class SystemServicesMgr;
	class ValidatorServicesMgr;

	class ServicesMgr
	{
	public:
		ServicesMgr(Context&);
		virtual ~ServicesMgr();

		ModelServicesMgr& getModelServicesMgr() const;
		SecurityServicesMgr& getSecurityServicesMgr() const;
		SystemServicesMgr& getSystemServicesMgr() const;
		ValidatorServicesMgr& getValidatorServicesMgr() const;

	private:
		Context& m_context;

		mutable std::unique_ptr<ModelServicesMgr> m_modelServicesMgr;
		mutable std::unique_ptr<SecurityServicesMgr> m_securityServicesMgr;
		mutable std::unique_ptr<SystemServicesMgr> m_systemServicesMgr;
		mutable std::unique_ptr<ValidatorServicesMgr> m_validatorServicesMgr;
	};

}}

