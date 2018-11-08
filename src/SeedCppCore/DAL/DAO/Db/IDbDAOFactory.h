#pragma once

#include <memory>


namespace seed_cpp { namespace model {
	class Patient;
	class User;
}}

namespace seed_cpp { namespace dal {

	class ILoadDAO;
	class ISaveDAO;
	class ITransactionDAO;

	class IDbDAOFactory
	{
	public:
		virtual ~IDbDAOFactory() = default;

		// ILoadDAO
		virtual std::unique_ptr<ILoadDAO> buildPatientLoadDAO() = 0;
		virtual std::unique_ptr<ILoadDAO> buildUserLoadDAO() = 0;

		// ISaveDAO
		template<typename _Entity>
		std::unique_ptr<ISaveDAO> buildEntitySaveDAO(_Entity& entity);

		virtual std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient&) = 0;
		virtual std::unique_ptr<ISaveDAO> buildUserSaveDAO(model::User&) = 0;

		// Transactions
		virtual std::unique_ptr<ITransactionDAO> startTransaction() = 0;
	};

}}
