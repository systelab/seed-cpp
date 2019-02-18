#include "LockableEntityMgrSubject.h"

#include "ILockableEntityMgrObserver.h"

#include <boost/thread/locks.hpp>


namespace seed_cpp { namespace model {

	LockableEntityMgrSubject::LockableEntityMgrSubject()
		:m_observers()
		,m_mutex(new boost::recursive_mutex())
	{
	}

	LockableEntityMgrSubject::LockableEntityMgrSubject(const LockableEntityMgrSubject& other)
		:m_observers(other.m_observers)
		,m_mutex(new boost::recursive_mutex())
	{
	}

	LockableEntityMgrSubject::~LockableEntityMgrSubject()
	{
	}

	void LockableEntityMgrSubject::registerObserver(ILockableEntityMgrObserver& observer)
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		m_observers.push_back(&observer);
	}

	void LockableEntityMgrSubject::unregisterObserver(ILockableEntityMgrObserver& observer)
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		std::vector<ILockableEntityMgrObserver*>::iterator it;
		it = std::find(m_observers.begin(), m_observers.end(), &observer);
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	}

	bool LockableEntityMgrSubject::isObserverRegistered(const ILockableEntityMgrObserver& observer) const
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		std::vector<ILockableEntityMgrObserver*>::const_iterator it = std::find( m_observers.begin(), m_observers.end(), &observer);
		return (it != m_observers.end());
	}

	void LockableEntityMgrSubject::notifyAdded(BaseEntity& entity, const IWriteLock& managerLock)
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		for (std::vector<ILockableEntityMgrObserver*>::const_iterator it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			(*it)->entityAdded(entity, managerLock);
		}
	}

	void LockableEntityMgrSubject::notifyEdited(BaseEntity& entity, const IWriteLock& managerLock)
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		for (std::vector<ILockableEntityMgrObserver*>::const_iterator it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			(*it)->entityEdited(entity, managerLock);
		}
	}

	void LockableEntityMgrSubject::notifyDeleted(BaseEntity& entity, const IWriteLock& managerLock)
	{
		boost::lock_guard<boost::recursive_mutex> lock(*m_mutex);
		for (std::vector<ILockableEntityMgrObserver*>::const_iterator it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			(*it)->entityDeleted(entity, managerLock);
		}
	}

}}
