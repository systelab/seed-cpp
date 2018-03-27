#include "StdAfx.h"
#include "EndpointRequestData.h"


namespace seed_cpp { namespace rest {

	EndpointRequestData::EndpointRequestData(const std::vector<RouteParam>& routeParameters,
											 const std::string& content,
											 const systelab::web_server::RequestQueryStrings& queryStrings)
		:m_routeParameters(routeParameters)
		,m_content(content)
		,m_queryStrings(queryStrings)
	{
	}
	
	EndpointRequestData::~EndpointRequestData()
	{
	}

	const std::vector<RouteParam>& EndpointRequestData::getRouteParameters() const
	{
		return m_routeParameters;
	}

	const std::string& EndpointRequestData::getContent() const
	{
		return m_content;
	}

	const systelab::web_server::RequestQueryStrings& EndpointRequestData::getQueryStrings() const
	{
		return m_queryStrings;
	}

}}

