#pragma once

#include <string>


namespace seed_cpp { namespace rest {

	class RouteFragment
	{
	public:
		RouteFragment(const std::string& item);
		virtual ~RouteFragment();

		bool isParameter() const;
		std::string getValue() const;

		bool match(const std::string& uriFragment) const;

	private:
		bool m_isParameter;
		std::string m_value;
	};

}}
