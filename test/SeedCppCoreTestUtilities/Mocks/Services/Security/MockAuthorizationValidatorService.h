#pragma once

#include "SeedCppCore/Services/Security/IAuthorizationValidatorService.h"

#include "WebServerAdapterInterface/Model/RequestHeaders.h"


namespace seed_cpp { namespace test_utility {

	class MockAuthorizationValidatorService : public service::IAuthorizationValidatorService
	{
	public:
		MockAuthorizationValidatorService();
		virtual ~MockAuthorizationValidatorService();

		MOCK_CONST_METHOD1(validate, bool(const systelab::web_server::RequestHeaders&));
	};

}}
