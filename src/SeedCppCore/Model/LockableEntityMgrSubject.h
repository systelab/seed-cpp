#pragma once

#include <boost/thread/recursive_mutex.hpp>


namespace seed_cpp { namespace model {

	class BaseEntity;
	class ILockableEntityMgrObserver;

	class LockableEntityMgrSubject
	{
	public:
		struct IReadLock
		{
			virtual ~IReadLock(){}
		};

		struct IWriteLock : public IReadLock
		{
			virtual ~IWriteLock(){}
		};

		LockableEntityMgrSubject();
		LockableEntityMgrSubject(const LockableEntityMgrSubject&);
		virtual ~LockableEntityMgrSubject();

		void registerObserver(ILockableEntityMgrObserver&);
		void unregisterObserver(ILockableEntityMgrObserver&);

		bool isObserverRegistered(const ILockableEntityMgrObserver&) const;

	protected:
		void notifyAdded(BaseEntity&, const IWriteLock&);
		void notifyEdited(BaseEntity&, const IWriteLock&);
		void notifyDeleted(BaseEntity&, const IWriteLock&);

	private:
		std::vector<ILockableEntityMgrObserver*> m_observers;
		std::unique_ptr<boost::recursive_mutex> m_mutex;
	};

}}

