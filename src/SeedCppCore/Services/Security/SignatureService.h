#pragma once

#include "ISignatureService.h"
#include "Services/Security/IBase64EncodeService.h"

namespace seed_cpp {
namespace service {

class SignatureService : public ISignatureService {
public:
  SignatureService(const IBase64EncodeService &);
  virtual ~SignatureService();

  std::string HMACSHA256(const std::string &key, const std::string &msg) const;
  std::string SHA256(const std::string &input) const;

private:
  const IBase64EncodeService &m_base64EncodeService;
};

} // namespace service
} // namespace seed_cpp
