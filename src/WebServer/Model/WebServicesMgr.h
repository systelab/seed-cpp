#pragma once

#include <memory>
#include <vector>


namespace systelab { namespace web_server {

	class IWebService;

	class WebServicesMgr
	{
	public:
		WebServicesMgr();
		virtual ~WebServicesMgr();

		unsigned int getWebServiceCount() const;
		const IWebService* getWebService(unsigned int index) const;
		void addWebService(std::unique_ptr<IWebService>);

	private:
		std::vector< std::unique_ptr<IWebService> > m_webServices;
	};

}}
