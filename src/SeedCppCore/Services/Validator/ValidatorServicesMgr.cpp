#include "stdafx.h"
#include "ValidatorServicesMgr.h"

#include "Services/Validator/IValidatorServicesFactory.h"
#include "Services/Validator/IJSONValidatorService.h"


namespace seed_cpp { namespace service {

	ValidatorServicesMgr::ValidatorServicesMgr(service::IValidatorServicesFactory& factory)
		:m_factory(factory)
		,m_jsonValidatorService()
	{
	}
	
	ValidatorServicesMgr::~ValidatorServicesMgr() = default;

	IJSONValidatorService& ValidatorServicesMgr::getJSONValidatorService() const
	{
		if (!m_jsonValidatorService.get())
		{
			m_jsonValidatorService = m_factory.buildJSONValidatorService();
		}

		return *m_jsonValidatorService;
	}

}}

