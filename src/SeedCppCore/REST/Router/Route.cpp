#include "StdAfx.h"
#include "Route.h"

#include "REST/Endpoints/IEndpoint.h"
#include "REST/Endpoints/EndpointRequestData.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "REST/Router/RouteParam.h"

#include "WebServerInterface/Model/Request.h"
#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	Route::Route(const std::string& method,
				 const std::string& uri,
				 std::function< std::unique_ptr<IEndpoint>(const EndpointRequestData&) > factoryMethod)
		:m_method(method)
		,m_fragments(buildFragmentsFromURI(uri))
		,m_factoryMethod(factoryMethod)
	{
	}

	Route::~Route()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> Route::execute(const systelab::web_server::Request& request) const
	{
		if (request.getMethod() != m_method)
		{
			return std::unique_ptr<systelab::web_server::Reply>();
		}

		std::vector<RouteFragment> requestFragments = buildFragmentsFromURI(request.getURI());
		if (requestFragments.size() != m_fragments.size())
		{
			return std::unique_ptr<systelab::web_server::Reply>();
		}

		std::vector<RouteParam> params;
		for (unsigned int i = 0; i < m_fragments.size(); i++)
		{
			const auto& requestFragment = requestFragments[i];
			if (requestFragment.isParameter())
			{
				return std::unique_ptr<systelab::web_server::Reply>();
			}

			const auto& fragment = m_fragments[i];
			if (!fragment.match(requestFragment.getValue()))
			{
				return std::unique_ptr<systelab::web_server::Reply>();
			}

			if (fragment.isParameter())
			{
				params.push_back(RouteParam(fragment.getValue(), requestFragment.getValue()));
			}
		}

		std::unique_ptr<IEndpoint> endpoint;
		try
		{
			EndpointRequestData requestData(params, request.getContent(), request.getHeaders(), request.getQueryStrings());
			endpoint = m_factoryMethod(requestData);
		}
		catch (std::exception&)
		{
		}

		if (!endpoint)
		{
			return std::unique_ptr<systelab::web_server::Reply>();
		}

		if (endpoint->hasAccess())
		{
			return endpoint->execute();
		}
		else
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::UNAUTHORIZED);
		}
	}

	std::vector<RouteFragment> Route::buildFragmentsFromURI(const std::string& uri) const
	{
		std::vector<RouteFragment> fragments;

		std::istringstream iss(uri);
		std::string item;

		while (std::getline(iss, item, '/'))
		{
			if (item.empty())
			{
				continue;
			}

			fragments.push_back(RouteFragment(item));
		}

		return fragments;
	}

}}
