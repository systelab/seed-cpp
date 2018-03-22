#include "StdAfx.h"
#include "RESTAPIWebService.h"

#include "WebServerInterface/Model/Reply.h"
#include "WebServerInterface/Model/Request.h"


namespace seed_cpp { namespace rest {

	RESTAPIWebService::RESTAPIWebService()
	{
	}

	RESTAPIWebService::~RESTAPIWebService()
	{
	}

	std::unique_ptr<systelab::web_server::Reply> RESTAPIWebService::process(const systelab::web_server::Request& request) const
	{
		return std::unique_ptr<systelab::web_server::Reply>();
	}

}}
