#pragma once

#include "LockableEntityMgrSubject.h"

namespace seed_cpp { namespace model {

	class ILockableEntityMgrObserver
	{
	public:
		virtual ~ILockableEntityMgrObserver() = default;

		virtual void entityAdded(BaseEntity&, const LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual void entityEdited(BaseEntity&, const LockableEntityMgrSubject::IWriteLock&) = 0;
		virtual void entityDeleted(BaseEntity&, const LockableEntityMgrSubject::IWriteLock&) = 0;
	};
}}

