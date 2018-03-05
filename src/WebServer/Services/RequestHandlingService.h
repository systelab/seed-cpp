#pragma once

#include "IRequestHandlingService.h"


namespace systelab { namespace web_server {

	class CORSConfiguration;
	class Request;
	class Reply;
	class WebServicesMgr;

	class RequestHandlingService : public IRequestHandlingService
	{
	public:
		RequestHandlingService(WebServicesMgr&,
							   CORSConfiguration&);
		virtual ~RequestHandlingService();

		std::unique_ptr<Reply> processRequest(const Request&) const;

	private:
		void addCORSHeaders(const Request& request, Reply& reply) const;

	private:
		WebServicesMgr& m_webServicesMgr;
		CORSConfiguration& m_corsConfiguration;
	};

}}

