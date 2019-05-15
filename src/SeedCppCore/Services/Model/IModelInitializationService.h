#pragma once

namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {

	class IModelInitializationService
	{
	public:
		virtual void initialize() = 0;
	};

}}