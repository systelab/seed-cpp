#pragma once

#include "LockableEntityMgrSubject.h"

#include <boost/thread/shared_mutex.hpp>
#include <memory>
#include <vector>

namespace seed_cpp { namespace model {

	template <class Entity> class EntityMgr : public LockableEntityMgrSubject
	{
	public:
		EntityMgr()
			:m_entities()
		{
		}

		EntityMgr(const EntityMgr<Entity> &other)
			:m_entities()
		{
			size_t nEntities = other.m_entities.size();
			for (size_t i = 0; i < nEntities; i++)
			{
				m_entities.push_back(std::make_unique<Entity>(*other.m_entities[i]));
			}
		}

		virtual ~EntityMgr<Entity>()
		{
		}

		struct SharedLock : public boost::shared_lock<boost::shared_mutex>,
							public IReadLock
		{
			SharedLock(EntityMgr<Entity> &mgr)
				:boost::shared_lock<boost::shared_mutex>(mgr.m_mutex)
			{
			}
		};

		struct UniqueLock : public boost::unique_lock<boost::shared_mutex>
						  , public IWriteLock
		{
			UniqueLock(EntityMgr<Entity>& mgr)
				:boost::unique_lock<boost::shared_mutex>(mgr.m_mutex)
			{
			}
		};

		unsigned int count() const
		{
			return (unsigned int)m_entities.size();
		}

		const Entity* getEntity(unsigned int index, const IReadLock&) const
		{
			return m_entities[index].get();
		}

		const Entity* getEntityById(const std::string& id, const IReadLock&) const
		{
			auto it = std::find_if(m_entities.begin(), m_entities.end(),
						[id](const std::unique_ptr<Entity> &entity)
						{
							return entity->getId() == id;
						});

			return ((it != m_entities.end()) ? it->get() : NULL);
		}

		const Entity& addEntity(std::unique_ptr<Entity> entity, const IWriteLock&)
		{
			m_entities.push_back(std::move(entity));
			return *m_entities.back();
		}

		const Entity& editEntity(std::unique_ptr<Entity> entity, const IWriteLock&)
		{
			if (!entity->getId())
			{
				throw std::runtime_error("EntityMgr<Entity>::editEntity(): Trying to edit an "
										 "entity without id");
			}

			std::string id = *entity->getId();
			for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++) {
				if ((*itr)->getId() == id) {
				itr->swap(entity);
				return **itr;
				}
			}

			throw std::string("EntityMgr<Entity>::deleteEntity: Trying to edit an "
							  "entity that it's not on manager");
		}

		void deleteEntity(const std::string &id, const IWriteLock &)
		{
			auto it = std::find_if(m_entities.begin(), m_entities.end(),
						[id](const std::unique_ptr<Entity> &entity)
						{
							return entity->getId() == id;
						});

			if (it != m_entities.end())
			{
				std::unique_ptr<Entity> entity;
				it->swap(entity);
				m_entities.erase(it);
			}
			else
			{
				throw std::string("EntityMgr<Entity>::deleteEntity Entity id not found");
			}
		}

		void setEntities(std::vector<std::unique_ptr<Entity>> entities, const IWriteLock&)
		{
			m_entities = std::move(entities);
		}

	private:
		std::vector<std::unique_ptr<Entity>> m_entities;
		boost::shared_mutex m_mutex;
	};

}}
