#pragma once

namespace seed_cpp { namespace service {

	class IModelLoaderService
	{
	public:
		virtual void loadModel() = 0;
	};

}}