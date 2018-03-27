#pragma once

#include <memory>
#include <vector>


namespace seed_cpp { namespace model {

	template <class Entity>
	class EntityMgr
	{
	public:
		EntityMgr()
			:m_entities()
		{
		}

		EntityMgr(const EntityMgr<Entity>& other)
			:m_entities(other.m_entities)
		{
		}

		virtual ~EntityMgr<Entity>()
		{
		}

		unsigned int count() const
		{
			return (unsigned int) m_entities.size();
		}

		const Entity* getEntity(unsigned int index) const
		{
			return m_entities[index].get();
		}

		const Entity* getEntityById(unsigned int id) const
		{
			auto it = std::find_if(m_entities.begin(), m_entities.end(),
				[id](const std::unique_ptr<Entity>& entity)
				{
					return entity->getId() == id;
				});
			return ((it != m_entities.end()) ? it->get() : NULL);
		}

		const Entity& addEntity(std::unique_ptr<Entity> entity)
		{
			m_entities.push_back(std::move(entity));
			return *m_entities.back();
		}

		const Entity& editEntity(std::unique_ptr<Entity> entity)
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

		void deleteEntity(unsigned int id)
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

		void setEntities(std::vector<std::unique_ptr<Entity> > entities)
		{
			m_entities = std::move(entities);
		}

	private:
		std::vector<std::unique_ptr<Entity> > m_entities;
	};

}}
