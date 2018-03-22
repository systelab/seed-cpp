#pragma once

#include "WebServerInterface/IWebService.h"
#include <memory>


namespace seed_cpp { namespace rest {

	class RESTAPIWebService : public systelab::web_server::IWebService
	{
	public:
		RESTAPIWebService();
		virtual ~RESTAPIWebService();

		std::unique_ptr<systelab::web_server::Reply> process(const systelab::web_server::Request& request) const;

	private:
		//Router m_router;
	};

}}
