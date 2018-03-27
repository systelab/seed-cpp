#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp {
	namespace dal {
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

	class PatientsGetAllEndpoint : public IEndpoint
	{
	public:
		PatientsGetAllEndpoint(model::EntityMgr<model::Patient>&,
							   dal::IJSONTranslatorsFactory&,
							   systelab::json_adapter::IJSONAdapter&);
		virtual ~PatientsGetAllEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		model::EntityMgr<model::Patient>& m_patientMgr;
		dal::IJSONTranslatorsFactory& m_jsonTranslatorsFactory;
		systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
	};

}}

