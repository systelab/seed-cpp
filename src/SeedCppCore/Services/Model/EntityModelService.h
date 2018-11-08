#pragma once

#include "DAL/DAO/ILoadDAO.h"
#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/ITransactionDAO.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "Model/EntityMgr.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"


namespace seed_cpp { namespace service {

	template <typename _Entity>
	class EntityModelService
	{
	public:
		EntityModelService(model::EntityMgr<_Entity>& entityMgr,
						   dal::IDbDAOFactory& daoFactory,
						   service::IUUIDGeneratorService& uuidGeneratorService,
						   service::ITimeService& timeService)
			:m_entityMgr(entityMgr)
			,m_daoFactory(daoFactory)
			,m_uuidGeneratorService(uuidGeneratorService)
			,m_timeService(timeService)
		{
		}

		virtual ~EntityModelService() = default;

		model::EntityMgr<_Entity>& getEntityMgr() const
		{
			return m_entityMgr;
		}

		const _Entity* getEntityById(const std::string& id) const
		{
			return m_entityMgr.getEntityById(id);
		}

		const _Entity& addEntity(std::unique_ptr<_Entity> entityToAdd)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				std::string uuid = m_uuidGeneratorService.generateUUID();
				entityToAdd->setId(uuid);

				boost::posix_time::ptime currentTime = m_timeService.getCurrentLocalTime();
				entityToAdd->setCreationTime(currentTime);
				entityToAdd->setUpdateTime(currentTime);

				auto dao = m_daoFactory.buildEntitySaveDAO(*entityToAdd);
				dao->addEntity();

				const _Entity& addedEntity = m_entityMgr.addEntity(std::move(entityToAdd));

				transaction->commit();

				return addedEntity;
			}
			catch (std::exception&)
			{
				transaction->rollback();
				throw;
			}
		}

		const _Entity& editEntity(std::unique_ptr<_Entity> entityToEdit)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				boost::posix_time::ptime currentTime = m_timeService.getCurrentLocalTime();
				entityToEdit->setUpdateTime(currentTime);

				auto dao = m_daoFactory.buildEntitySaveDAO(*entityToEdit);
				dao->updateEntity();

				const _Entity& editedEntity = m_entityMgr.editEntity(std::move(entityToEdit));

				transaction->commit();

				return editedEntity;
			}
			catch (std::exception&)
			{
				transaction->rollback();
				throw;
			}
		}

		void deleteEntity(const std::string& id)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				const _Entity* entityToDelete = m_entityMgr.getEntityById(id);
				if (entityToDelete)
				{
					_Entity entityToDeleteCopy = *entityToDelete;
					auto dao = m_daoFactory.buildEntitySaveDAO(entityToDeleteCopy);
					dao->deleteEntity();
					m_entityMgr.deleteEntity(id);
				}
				else
				{
					throw std::runtime_error("EntityModelService::deleteEntity: Entity with given id not found");
				}

				transaction->commit();
			}
			catch (std::exception&)
			{
				transaction->rollback();
				throw;
			}
		}

	protected:
		model::EntityMgr<_Entity>& m_entityMgr;
		dal::IDbDAOFactory& m_daoFactory;
		service::IUUIDGeneratorService& m_uuidGeneratorService;
		service::ITimeService& m_timeService;
	};

}}
