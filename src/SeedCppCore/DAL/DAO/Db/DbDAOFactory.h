#pragma once

#include "../ITransactionDAOMgr.h"
#include "IDbDAOFactory.h"

namespace seed_cpp {
class Core;
}

namespace seed_cpp {
namespace dal {

class DbDAOFactory : public IDbDAOFactory, public ITransactionDAOMgr {
public:
  DbDAOFactory(Core &core);
  virtual ~DbDAOFactory();

  std::unique_ptr<ILoadDAO> buildPatientLoadDAO();
  std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient &);

  // Users
  std::unique_ptr<ILoadDAO> buildUserLoadDAO();
  std::unique_ptr<ISaveDAO> buildUserSaveDAO(model::User &);

  // Transactions
  std::unique_ptr<ITransactionDAO> startTransaction();

  void releaseTransactionInProgress();

protected:
  Core &m_core;
  bool m_transactionInProgress;
};

} // namespace dal
} // namespace seed_cpp
