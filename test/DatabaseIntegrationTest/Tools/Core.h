#pragma once

namespace seed_cpp {

	class Context;

	namespace model {
		class Model;
	}
	namespace service {
		class ServicesMgr;
	}
}

namespace seed_cpp { namespace db_test {

	class Core
	{
	public:
		Core(const std::string&);
		virtual ~Core();

		void initialize();

		model::Model& getModel();
		service::ServicesMgr& getServicesMgr();

	protected:
		void buildModel();
		void buildFactories();
		void buildServices();

		void initializeModel();

	private:
		std::string m_databaseFilepath;
		std::unique_ptr<Context> m_context;
	};

}}