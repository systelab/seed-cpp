#pragma once

#include <stdexcept>
#include <string>

namespace systelab {
namespace json_adapter {
class IJSONDocument;
}
} // namespace systelab

namespace seed_cpp {
namespace service {

class IJSONValidatorService {
public:
  virtual ~IJSONValidatorService(){};

  virtual void validate(const systelab::json_adapter::IJSONDocument &,
                        const std::string &schemaName) const = 0;

public:
  struct JSONValidationException : public std::runtime_error {
    JSONValidationException(const std::string &message)
        : std::runtime_error(message.c_str()) {}
    virtual std::string toString() const { return what(); };
  };
};

} // namespace service
} // namespace seed_cpp
