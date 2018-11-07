#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/optional.hpp>
#include <string>


namespace seed_cpp { namespace model {

	class BaseEntity
	{
	public:
		BaseEntity();
		BaseEntity(const BaseEntity&);
		virtual ~BaseEntity() = default;

		boost::optional<std::string> getId() const;
		boost::posix_time::ptime getCreationTime() const;
		boost::posix_time::ptime getUpdateTime() const;

		void setId(const boost::optional<std::string>&);
		void setCreationTime(const boost::posix_time::ptime&);
		void setUpdateTime(const boost::posix_time::ptime&);

		BaseEntity& operator= (const BaseEntity&);
		friend bool operator== (const BaseEntity&, const BaseEntity&);
		friend bool operator!= (const BaseEntity&, const BaseEntity&);

	private:
		boost::optional<std::string> m_id;
		boost::posix_time::ptime m_creationTime;
		boost::posix_time::ptime m_updateTime;
	};

}}
