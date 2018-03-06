#pragma once

#include <memory>
#include <vector>


namespace seed_cpp { namespace model {

	template <class Entity>
	class EntityMgr
	{
	public:
		EntityMgr();
		EntityMgr(const EntityMgr<Entity>&);
		virtual ~EntityMgr();

		unsigned int count() const;

		const Entity* getEntity(unsigned int index) const;
		const Entity* getEntityById(unsigned int id) const;

		const Entity& addEntity(std::unique_ptr<Entity>);
		const Entity& editEntity(std::unique_ptr<Entity>);
		void deleteEntity(unsigned int id);

		void setEntities(std::vector<std::unique_ptr<Entity> >);

	private:
		std::vector<std::unique_ptr<Entity> > m_entities;
	};

}}
