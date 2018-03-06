#include "StdAfx.h"
#include "EntityMgr.h"


namespace seed_cpp { namespace model {

	template <class Entity>
	EntityMgr<Entity>::EntityMgr()
		:m_entities()
	{
	}

	template <class Entity>
	EntityMgr<Entity>::EntityMgr(const EntityMgr<Entity>& other)
		:m_entities(other.m_entities)
	{
	}

	template <class Entity>
	EntityMgr<Entity>::~EntityMgr()
	{
	}

	template <class Entity>
	unsigned int EntityMgr<Entity>::count() const
	{
		m_entities.size();
	}

	template <class Entity>
	const Entity* EntityMgr<Entity>::getEntity(unsigned int index) const
	{
		return m_entities[index].get();
	}

	template <class Entity>
	const Entity* EntityMgr<Entity>::getEntityById(unsigned int id) const
	{
		auto it = std::find_if(m_entities.begin(), m_entities.end(),
					[id](const std::unique_ptr<Entity>& entity)
					{
						return entity->getId() == recordId;
					});
		return ((it != m_entities.end()) ? it->get() : NULL);
	}

	template <class Entity>
	const Entity& EntityMgr<Entity>::addEntity(std::unique_ptr<Entity> entity)
	{
		m_entities.push_back(std::move(entity));
		return *m_entities.back();
	}

	template <class Entity>
	const Entity& EntityMgr<Entity>::editEntity(std::unique_ptr<Entity> entity)
	{
		if (!entity->getId())
		{
			throw std::exception("EntityMgr<Entity>::editEntity(): Trying to edit an entity without id");
		}

		unsigned int id = *entity->getId();
		for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
		{
			if ((*itr)->getId() == id)
			{
				itr->swap(entity);
				return **itr;
			}
		}

		throw std::exception("EntityMgr<Entity>::deleteEntity: Trying to edit an entity that it's not on manager");
	}

	template <class Entity>
	void EntityMgr<Entity>::deleteEntity(unsigned int id)
	{
		auto it = std::find_if(m_entities.begin(), m_entities.end(),
					[id](const std::unique_ptr<Entity>& entity)
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
			throw std::exception("EntityMgr<Entity>::deleteEntity Entity id not found");
		}
	}

	template <class Entity>
	void EntityMgr<Entity>::setEntities(std::vector<std::unique_ptr<Entity>> entities)
	{
		m_entities = std::move(entities);
	}

}}
