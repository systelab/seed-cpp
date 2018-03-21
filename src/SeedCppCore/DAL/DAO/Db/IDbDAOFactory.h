#pragma once

#include "Model/EntityMgr.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace dal {

	class ILoadDAO;
	class ISaveDAO;
	class ITransactionDAO;

	class IDbDAOFactory
	{
	public:
		virtual ~IDbDAOFactory() {};

		virtual std::unique_ptr<ILoadDAO> buildPatientLoadDAO(model::EntityMgr<model::Patient>&) = 0;
		virtual std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient&) = 0;

		virtual std::unique_ptr<ITransactionDAO> startTransaction() = 0;
	};

}}
