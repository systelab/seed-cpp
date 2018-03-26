#pragma once

#include "REST/Endpoints/IEndpoint.h"
#include "REST/Router/RouteFragment.h"
#include "REST/Router/RouteParam.h"

#include <memory>
#include <string>


namespace systelab { namespace web_server {
	class Reply;
	class Request;
}}

namespace seed_cpp { namespace rest {

	class Route
	{
	public:
		Route(const std::string& method,
			  const std::string& uri,
			  std::function< std::unique_ptr<IEndpoint>(const std::vector<RouteParam>&) > factoryMethod);
		virtual ~Route();

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::web_server::Request&) const;

	private:
		std::vector<RouteFragment> buildFragmentsFromURI(const std::string& uri) const;

	private:
		std::string m_method;
		std::vector<RouteFragment> m_fragments;
		std::function< std::unique_ptr<IEndpoint>(const std::vector<RouteParam>&) > m_factoryMethod;
	};

}}
