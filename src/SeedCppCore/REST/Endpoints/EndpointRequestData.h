#pragma once

#include "REST/Router/RouteParam.h"

#include "WebServerInterface/Model/RequestHeaders.h"
#include "WebServerInterface/Model/RequestQueryStrings.h"

#include <memory>
#include <string>
#include <vector>


namespace seed_cpp { namespace rest {

	class EndpointRequestData
	{
	public:
		EndpointRequestData(const std::vector<RouteParam>&,
							const std::string&,
							const systelab::web_server::RequestHeaders&,
							const systelab::web_server::RequestQueryStrings&);
		virtual ~EndpointRequestData();

		const std::vector<RouteParam>& getRouteParameters() const;
		const std::string& getContent() const;
		const systelab::web_server::RequestHeaders& getHeaders() const;
		const systelab::web_server::RequestQueryStrings& getQueryStrings() const;

	private:
		const std::vector<RouteParam> m_routeParameters;
		const std::string m_content;
		const systelab::web_server::RequestHeaders m_headers;
		const systelab::web_server::RequestQueryStrings m_queryStrings;
	};

}}

