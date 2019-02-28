#pragma once

#include "IDatabaseEntityTranslator.h"
#include <string>

namespace seed_cpp {
namespace model {
class Address;
}
} // namespace seed_cpp

namespace seed_cpp {
namespace dal {

class AddressDbTranslator : public IDatabaseEntityTranslator {
public:
  AddressDbTranslator(const std::string &patientId, model::Address &);
  virtual ~AddressDbTranslator();

  void fillEntityFromRecord(const systelab::db::ITableRecord &);
  void fillRecordFromEntity(systelab::db::ITableRecord &) const;

private:
  std::string m_patientId;
  model::Address &m_address;
};

} // namespace dal
}; // namespace seed_cpp
