#include "ResourceService.h"

#include <fstream>
#include <sstream>
#include <string>

#pragma warning(disable : 4996)

namespace seed_cpp {
namespace service {

ResourceService::ResourceService() {}

ResourceService::~ResourceService() {}

std::string
ResourceService::loadResourceAsString(unsigned int resourceId,
                                      const std::string &resourceType) const {
  //  size_t count = 0;
  //  std::wstring resourceTypeWStr(resourceType.size(), L' ');
  //  resourceTypeWStr.resize(std::mbstowcs(
  //      &resourceTypeWStr[0], resourceType.c_str(), resourceType.size()));

  //  HMODULE hndModule = GetModuleHandle(NULL);
  //  HRSRC hndResource = FindResource(hndModule, MAKEINTRESOURCE(resourceId),
  //                                   resourceTypeWStr.c_str());
  //  if (!hndResource) {
  //    throw std::runtime_error("Resource not found. Error: " +
  //                             getSystemErrorMessage());
  //  }

  //  DWORD size = SizeofResource(NULL, hndResource);
  //  HGLOBAL hndGlobal = LoadResource(NULL, hndResource);
  //  if (!hndGlobal) {
  //    throw std::runtime_error("Load resource " +
  //                             std::to_string((long long)resourceId) +
  //                             " failed. Error: " + getSystemErrorMessage());
  //  }

  //  LPVOID resource = LockResource(hndGlobal);
  //  std::string resourceContent(reinterpret_cast<char *>(resource), size);

  //  return resourceContent;
  (void)resourceId;
  return resourceType;
}

std::string
ResourceService::loadResourceAsString(const std::string &resourceId,
                                      const std::string &resourceType) const {
  //  std::wstring resourceIdWStr(resourceId.size(), L' ');
  //  resourceIdWStr.resize(
  //      std::mbstowcs(&resourceIdWStr[0], resourceId.c_str(),
  //      resourceId.size()));

  //  std::wstring resourceTypeWStr(resourceType.size(), L' ');
  //  resourceTypeWStr.resize(std::mbstowcs(
  //      &resourceTypeWStr[0], resourceType.c_str(), resourceType.size()));

  //  HMODULE hndModule = GetModuleHandle(NULL);
  //  HRSRC hndResource =
  //      FindResource(hndModule, resourceIdWStr.c_str(),
  //      resourceTypeWStr.c_str());
  //  if (!hndResource) {
  //    throw std::runtime_error("Resource not found. Error: " +
  //                             getSystemErrorMessage());
  //  }

  //  DWORD size = SizeofResource(NULL, hndResource);
  //  HGLOBAL hndGlobal = LoadResource(NULL, hndResource);
  //  if (!hndGlobal) {
  //    throw std::runtime_error("Load resource " + resourceId +
  //                             " failed. Error: " + getSystemErrorMessage());
  //  }

  //  LPVOID resource = LockResource(hndGlobal);
  //  std::string resourceContent(reinterpret_cast<char *>(resource), size);

  //  return resourceContent;
  //}

  // std::string ResourceService::getSystemErrorMessage() const {
  //  WCHAR buffer[256];
  //  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
  //                LANG_SYSTEM_DEFAULT, buffer, 256, NULL);

  //  std::wstring bufferWstr(buffer);
  //  return std::string(bufferWstr.begin(), bufferWstr.end());
  (void)resourceId;
  return resourceType;
}

} // namespace service
} // namespace seed_cpp
