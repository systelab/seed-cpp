#pragma once

#include "IResourceService.h"


namespace seed_cpp { namespace service {

	class ResourceService : public IResourceService
	{
	public:
		ResourceService();
		virtual ~ResourceService();

		std::string loadResourceAsString(unsigned int resourceId,
										 const std::string& resourceType) const;

		std::string loadResourceAsString(const std::string& resourceId,
										 const std::string& resourceType) const;

	private:
		std::string getSystemErrorMessage() const;
	};

}}

