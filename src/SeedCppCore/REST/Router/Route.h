#pragma once

#include "REST/Router/RouteFragment.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>


namespace systelab { namespace web_server {
	class Reply;
	class Request;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint;
	class EndpointRequestData;

	class Route
	{
	public:
		Route(const std::string& method,
			  const std::string& uri,
			  std::function< std::unique_ptr<IEndpoint>(const EndpointRequestData&) > factoryMethod);
		virtual ~Route();

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::web_server::Request&) const;

	private:
		std::vector<RouteFragment> buildFragmentsFromURI(const std::string& uri) const;

	private:
		std::string m_method;
		std::vector<RouteFragment> m_fragments;
		std::function< std::unique_ptr<IEndpoint>(const EndpointRequestData&) > m_factoryMethod;
	};

}}
