#pragma once

#include <string>
#include <boost/lexical_cast.hpp>


namespace seed_cpp { namespace rest {

	class RouteParam
	{
	public:
		RouteParam(const std::string& name, const std::string& value)
			:m_name(name)
			,m_value(value)
		{}

		virtual ~RouteParam() {};

		std::string getName() const
		{
			return m_name;
		}

		template<typename T> T getValue() const
		{
			return boost::lexical_cast<T>(m_value);
		}

	private:
		std::string m_name;
		std::string m_value;
	};

}}
