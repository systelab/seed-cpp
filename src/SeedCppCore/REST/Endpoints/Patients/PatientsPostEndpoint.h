#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp {
	namespace dal {
		class IDbDAOFactory;
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class Patient;
	}
}

namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint;

	class PatientsPostEndpoint : public IEndpoint
	{
	public:
		PatientsPostEndpoint(const std::string& requestContent,
							 model::EntityMgr<model::Patient>&,
							 dal::IDbDAOFactory&,
							 dal::IJSONTranslatorsFactory&,
							 systelab::json_adapter::IJSONAdapter&);
		virtual ~PatientsPostEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		std::string m_requestContent;
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IDbDAOFactory& m_dbDAOFactory;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
	};

}}

