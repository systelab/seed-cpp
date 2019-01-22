#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "WebServerInterface/Model/RequestHeaders.h"
#include "WebServerInterface/Model/RequestQueryStrings.h"


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class User;
	}
	namespace service {
		class IAuthorizationValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class UsersGetAllEndpoint : public IEndpoint
	{
	public:
		UsersGetAllEndpoint(const systelab::web_server::RequestHeaders&,
							const systelab::web_server::RequestQueryStrings&,
							model::EntityMgr<model::User>&,
							dal::IJSONTranslatorsFactory&,
							systelab::json_adapter::IJSONAdapter&,
							service::IAuthorizationValidatorService&);
		virtual ~UsersGetAllEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		struct PaginationData
		{
			std::vector<model::User> m_content;
			unsigned int m_totalElements;
			bool m_first;
			bool m_last;
			unsigned int m_number;
			unsigned int m_numberOfElements;
			unsigned int m_size;
			unsigned int m_totalPages;
		};

		std::unique_ptr<PaginationData> getPaginationData() const;

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const systelab::web_server::RequestQueryStrings m_queryStrings;
		model::EntityMgr<model::User>& m_userMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

