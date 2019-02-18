#pragma once

#include "IWebService.h"
#include <memory>


namespace seed_cpp { namespace rest {

	class IEndpointsFactory;
	class Router;

	class RESTAPIWebService : public systelab::web_server::IWebService
	{
	public:
		RESTAPIWebService(IEndpointsFactory&);
		virtual ~RESTAPIWebService();

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request& request) const;

	private:
		IEndpointsFactory& m_endpointsFactory;
		std::unique_ptr<Router> m_router;
	};

}}
