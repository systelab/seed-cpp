#include "StdAfx.h"
#include "BaseEntity.h"

#include "Address.h"


namespace seed_cpp { namespace model {

	BaseEntity::BaseEntity()
		:m_id()
		,m_creationTime()
		,m_updateTime()
	{
	}

	BaseEntity::BaseEntity(const BaseEntity& other)
		:m_id(other.m_id)
		,m_creationTime(other.m_creationTime)
		,m_updateTime(other.m_updateTime)
	{
	}

	boost::optional<std::string> BaseEntity::getId() const
	{
		return m_id;
	}

	boost::posix_time::ptime BaseEntity::getCreationTime() const
	{
		return m_creationTime;
	}
	
	boost::posix_time::ptime BaseEntity::getUpdateTime() const
	{
		return m_updateTime;
	}

	void BaseEntity::setId(const boost::optional<std::string>& id)
	{
		m_id = id;
	}

	void BaseEntity::setCreationTime(const boost::posix_time::ptime& creationTime)
	{
		m_creationTime = creationTime;
	}

	void BaseEntity::setUpdateTime(const boost::posix_time::ptime& updateTime)
	{
		m_updateTime = updateTime;
	}

	BaseEntity& BaseEntity::operator= (const BaseEntity& other)
	{
		m_id = other.m_id;
		m_creationTime = other.m_creationTime;
		m_updateTime = other.m_updateTime;

		return *this;
	}

	bool operator== (const BaseEntity& lhs, const BaseEntity& rhs)
	{
		if ( (lhs.m_id != rhs.m_id) ||
			 (lhs.m_creationTime != rhs.m_creationTime) ||
			 (lhs.m_updateTime != rhs.m_updateTime) )
		{
			return false;
		}

		return true;
	}

	bool operator!= (const BaseEntity& lhs, const BaseEntity& rhs)
	{
		return !(lhs == rhs);
	}

}}
