#pragma once

#include "IContextBuilderService.h"


namespace seed_cpp { namespace service {
	
	class ContextBuilderService : public IContextBuilderService
	{
	public:
		ContextBuilderService(Context&);
		virtual ~ContextBuilderService();

		void buildFactories() override;
		void buildModel() override;
		void buildServices() override;

	private:
		Context& m_context;
	};

}}
