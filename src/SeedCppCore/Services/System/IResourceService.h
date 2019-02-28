#pragma once

#include <string>

namespace seed_cpp {
namespace service {

class IResourceService {
public:
  virtual ~IResourceService(){};

  virtual std::string
  loadResourceAsString(unsigned int resourceId,
                       const std::string &resourceType) const = 0;

  virtual std::string
  loadResourceAsString(const std::string &resourceId,
                       const std::string &resourceType) const = 0;
};

} // namespace service
} // namespace seed_cpp
