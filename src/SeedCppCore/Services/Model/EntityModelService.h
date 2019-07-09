#pragma once

#pragma warning (push)
#pragma warning (disable: 4346)

#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/ITransactionDAO.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "Model/LockableEntityMgrSubject.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"


namespace seed_cpp { namespace service {

	template <typename _Entity, typename _EntityMgr>
	class EntityModelService
	{
	private:
		typedef std::function<std::unique_ptr<dal::ISaveDAO>(_Entity&)> DAOFactoryMethod;
	public:
		EntityModelService(_EntityMgr& entityMgr,
							dal::IDbDAOFactory& daoFactory,
							DAOFactoryMethod factoryMethod,
							service::IUUIDGeneratorService& uuidGeneratorService,
							service::ITimeService& timeService)
			:m_entityMgr(entityMgr)
			,m_daoFactory(daoFactory)
			,m_factoryMethod(factoryMethod)
			,m_uuidGeneratorService(uuidGeneratorService)
			,m_timeService(timeService)
		{
		}

		virtual ~EntityModelService() = default;

		_EntityMgr& getEntityMgr() const
		{
			return m_entityMgr;
		}

		const _Entity* getEntityById(const std::string& id,
									 const model::LockableEntityMgrSubject::IReadLock& readLock) const
		{
			return m_entityMgr.getEntityById(id, readLock);
		}

		const _Entity& addEntity(std::unique_ptr<_Entity> entityToAdd,
								 const model::LockableEntityMgrSubject::IWriteLock& writeLock)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				if (!entityToAdd->getId())
				{
					std::string uuid = m_uuidGeneratorService.generateUUID();
					entityToAdd->setId(uuid);
				}

				boost::posix_time::ptime currentTime = m_timeService.getCurrentLocalTime();
				entityToAdd->setCreationTime(currentTime);
				entityToAdd->setUpdateTime(currentTime);

				auto dao = m_factoryMethod(*entityToAdd);
				dao->addEntity();

				const _Entity& addedEntity = m_entityMgr.addEntity(std::move(entityToAdd), writeLock);

				transaction->commit();

				return addedEntity;
			}
			catch (std::exception&)
			{
				transaction->rollback();
				throw;
			}
		}

		const _Entity& editEntity(std::unique_ptr<_Entity> entityToEdit,
								  const model::LockableEntityMgrSubject::IWriteLock& writeLock)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				boost::posix_time::ptime currentTime = m_timeService.getCurrentLocalTime();
				entityToEdit->setUpdateTime(currentTime);

				auto dao = m_factoryMethod(*entityToEdit);
				dao->updateEntity();

				const _Entity& editedEntity = m_entityMgr.editEntity(std::move(entityToEdit), writeLock);

				transaction->commit();

				return editedEntity;
			}
			catch (std::exception&)
			{
				transaction->rollback();
				throw;
			}
		}

		void deleteEntity(const std::string& id, const model::LockableEntityMgrSubject::IWriteLock& writeLock)
		{
			auto transaction = m_daoFactory.startTransaction();

			try
			{
				const _Entity* entityToDelete = m_entityMgr.getEntityById(id, writeLock);
				if (entityToDelete)
				{
					_Entity entityToDeleteCopy = *entityToDelete;
					auto dao = m_factoryMethod(entityToDeleteCopy);
					dao->deleteEntity();
					m_entityMgr.deleteEntity(id, writeLock);
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

		std::unique_ptr<model::LockableEntityMgrSubject::IReadLock> createReadLock()
		{
			return std::make_unique<typename _EntityMgr::SharedLock>(m_entityMgr);
		}

		std::unique_ptr<model::LockableEntityMgrSubject::IWriteLock> createWriteLock()
		{
			return std::make_unique<typename _EntityMgr::UniqueLock>(m_entityMgr);
		}

	protected:
		_EntityMgr& m_entityMgr;
		dal::IDbDAOFactory& m_daoFactory;
		DAOFactoryMethod m_factoryMethod;
		service::IUUIDGeneratorService& m_uuidGeneratorService;
		service::ITimeService& m_timeService;
	};

}}
