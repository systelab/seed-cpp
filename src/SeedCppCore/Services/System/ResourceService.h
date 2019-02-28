#pragma once

#include "IResourceService.h"
#include <map>

namespace seed_cpp {
namespace service {

class ResourceService : public IResourceService {
public:
  ResourceService();
  virtual ~ResourceService();

  static const std::string schemaPath;
  static const std::string schemaPatientPost;
  static const std::string schemaPatientPut;
  static const std::string schemaUserPost;
  static const std::string schemaUserPut;
  static const std::string schemaModelPatient;
  static const std::string schemaModelAddress;
  static const std::string schemaModelUser;

  std::string loadResourceAsString(unsigned int resourceId,
                                   const std::string &resourceType) const;

  std::string loadResourceAsString(const std::string &resourceId,
                                   const std::string &resourceType) const;

private:
  bool LoadSchema(const std::string &file);

  std::map<const std::string, std::string> schemas_;
  std::string getSystemErrorMessage() const;
};

} // namespace service
} // namespace seed_cpp
