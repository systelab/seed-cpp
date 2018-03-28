#pragma once

#include "Model/EntityMgr.h"
#include "REST/Endpoints/IEndpoint.h"


namespace seed_cpp { namespace model {
	class User;
}}

namespace seed_cpp { namespace rest {

	class UsersLoginPostEndpoint : public IEndpoint
	{
	public:
		UsersLoginPostEndpoint(const std::string& requestContent,
							   model::EntityMgr<model::User>&);
		virtual ~UsersLoginPostEndpoint();

		std::unique_ptr<systelab::web_server::Reply> execute();

	private:
		std::string m_requestContent;
		model::EntityMgr<model::User>& m_userMgr;
	};

}}

