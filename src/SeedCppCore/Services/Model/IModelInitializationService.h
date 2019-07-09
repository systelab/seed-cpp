#pragma once

namespace seed_cpp { namespace service {

	class IModelInitializationService
	{
	public:
		virtual ~IModelInitializationService() = default;

		virtual void initialize() = 0;
	};

}}