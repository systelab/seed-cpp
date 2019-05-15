#pragma once

#include "IModelInitializationService.h"


namespace seed_cpp { namespace service {
	
	class ModelInitializationService : public IModelInitializationService
	{
	public:
		ModelInitializationService(Context&);
		virtual ~ModelInitializationService();

		void initialize() override;

	protected:
		void loadUsers();
		void loadPatients();

	private:
		Context& m_context;
	};

}}
