#pragma once

namespace seed_cpp { namespace service {

	class IJSONValidatorService;
	class IValidatorServicesFactory;

	class ValidatorServicesMgr
	{
	public:
		ValidatorServicesMgr(service::IValidatorServicesFactory&);
		virtual ~ValidatorServicesMgr();

		IJSONValidatorService& getJSONValidatorService() const;

	private:
		IValidatorServicesFactory& m_factory;

		mutable std::unique_ptr<IJSONValidatorService> m_jsonValidatorService;
	};

}}

