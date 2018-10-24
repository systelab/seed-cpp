#pragma once

#include <string>


namespace seed_cpp { namespace service {

	class IUUIDGeneratorService
	{
	public:
		virtual ~IUUIDGeneratorService() = default;

		virtual std::string generateUUID() = 0;
	};

}}
