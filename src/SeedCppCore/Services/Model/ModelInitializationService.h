#pragma once

#include "IModelInitializationService.h"


namespace seed_cpp {
	class Context;
}

namespace seed_cpp { namespace service {
	
	class ModelInitializationService : public IModelInitializationService
	{
	public:
		ModelInitializationService(Context&);
		virtual ~ModelInitializationService();

		void initialize() override;

	protected:
		void loadModel();
		void createDefaultUsers();

	private:
		Context& m_context;
	};

}}
