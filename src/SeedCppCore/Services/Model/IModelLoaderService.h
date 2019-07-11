#pragma once

namespace seed_cpp { namespace service {

	class IModelLoaderService
	{
	public:
		virtual ~IModelLoaderService() = default;

		virtual void loadModel() = 0;
	};

}}