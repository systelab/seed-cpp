#pragma once

#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONRemoteSchemaProvider.h"

#include <memory>


namespace systelab { namespace json_adapter {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace service {

	class IResourceService;

	class JSONValidatorService : public IJSONValidatorService
	{
	private:
		class RemoteSchemaDocumentProvider : public systelab::json_adapter::IJSONRemoteSchemaProvider
		{
		public:
			RemoteSchemaDocumentProvider(const service::IResourceService&,
										 const systelab::json_adapter::IJSONAdapter&);
			virtual ~RemoteSchemaDocumentProvider() = default;

			std::unique_ptr<systelab::json_adapter::IJSONDocument> getRemoteSchemaDocument(const std::string& uri) const;

		private:
			const service::IResourceService& m_resourceService;
			const systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		};

	public:
		JSONValidatorService(const service::IResourceService&,
							 const systelab::json_adapter::IJSONAdapter&);
		virtual ~JSONValidatorService() = default;

		void validate(const systelab::json_adapter::IJSONDocument&, const std::string& schemaName) const;

	private:
		const systelab::json_adapter::IJSONAdapter& m_jsonAdapter;
		std::unique_ptr<RemoteSchemaDocumentProvider> m_documentProvider;
	};

}}

