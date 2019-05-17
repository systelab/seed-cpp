#pragma once

#include "IModelLoaderService.h"

namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {
	
	class ModelLoaderService : public IModelLoaderService
	{
	public:
		ModelLoaderService(Context&);
		virtual ~ModelLoaderService();

		void loadModel() override;

	protected:
		void loadUsers();
		void loadPatients();

	private:
		Context& m_context;
	};

}}
