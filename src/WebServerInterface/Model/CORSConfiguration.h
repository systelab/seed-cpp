#pragma once

#include <set>


namespace systelab { namespace web_server {

	class CORSConfiguration
	{
	public:
		CORSConfiguration();
		CORSConfiguration(const CORSConfiguration&);
		virtual ~CORSConfiguration();

		bool isEnabled() const;
		bool isAllowedOrigin(const std::string&) const;
		std::string getAllowedHeaders() const;
		std::string getAllowedMethods() const;
		bool areAllowedCredentials() const;
		unsigned int getMaxAge() const;
		std::string getExposedHeaders() const;

		void setEnabled(bool enabled);
		void addAllowedOrigin(const std::string&);
		void setAllowedHeaders(const std::string&);
		void setAllowedMethods(const std::string&);
		void setAllowedCredentials(bool);
		void setMaxAge(unsigned int);
		void setExposedHeaders(const std::string&);

		CORSConfiguration& operator= (const CORSConfiguration& other);

	private:
		bool m_enabled;
		std::set<std::string> m_allowedOrigins;
		std::string m_allowedHeaders;
		std::string m_allowedMethods;
		bool m_allowedCredentials;
		unsigned int m_maxAge;
		std::string m_exposedHeaders;
	};

}}
