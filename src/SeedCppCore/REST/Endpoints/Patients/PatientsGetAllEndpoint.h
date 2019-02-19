#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"

#include "Model/RequestHeaders.h"
#include "Model/RequestQueryStrings.h"


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp {
	namespace dal {
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class Patient;
	}
	namespace service {
		class IAuthorizationValidatorService;
	}
}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsGetAllEndpoint : public IEndpoint
	{
	public:
		PatientsGetAllEndpoint(const systelab::web_server::RequestHeaders&,
							   const systelab::web_server::RequestQueryStrings&,
							   model::EntityMgr<model::Patient>&,
							   dal::IJSONTranslatorsFactory&,
							   systelab::json_adapter::IJSONAdapter&,
							   service::IAuthorizationValidatorService&);
		virtual ~PatientsGetAllEndpoint();

		bool hasAccess() const;
		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		struct PaginationData
		{
			std::vector<model::Patient> m_content;
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
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}

