#include "StdAfx.h"
#include "WebServicesMgr.h"

#include "WebServerInterface/IWebService.h"


namespace systelab { namespace web_server {

	WebServicesMgr::WebServicesMgr()
		:m_webServices()
	{
	}

	WebServicesMgr::~WebServicesMgr()
	{
	}

	unsigned int WebServicesMgr::getWebServiceCount() const
	{
		return (unsigned int) m_webServices.size();
	}

	const IWebService* WebServicesMgr::getWebService(unsigned int index) const
	{
		return (m_webServices[index]).get();
	}

	void WebServicesMgr::addWebService(std::unique_ptr<IWebService> webService)
	{
		m_webServices.push_back(std::move(webService));
	}

}}
