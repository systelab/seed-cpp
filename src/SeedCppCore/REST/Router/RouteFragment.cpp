#include "RouteFragment.h"


namespace seed_cpp { namespace rest {

	RouteFragment::RouteFragment(const std::string& fragment)
	{
		m_isParameter = (fragment[0] == ':');
		m_value = m_isParameter ? fragment.substr(1) : fragment;
	}

	RouteFragment::~RouteFragment()
	{
	}

	bool RouteFragment::isParameter() const
	{
		return m_isParameter;
	}

	std::string RouteFragment::getValue() const
	{
		return m_value;
	}

	bool RouteFragment::match(const std::string& uriFragment) const
	{
		if (m_isParameter)
		{
			return true;
		}
		else
		{
			return (uriFragment == m_value);
		}
	}

}}
