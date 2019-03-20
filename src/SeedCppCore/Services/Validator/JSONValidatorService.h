#pragma once

#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONRemoteSchemaProvider.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace seed_cpp { namespace service {

	class IResourceService;

	class JSONValidatorService : public IJSONValidatorService
	{
	private:
		class RemoteSchemaDocumentProvider : public systelab::json::IJSONRemoteSchemaProvider
		{
		public:
			RemoteSchemaDocumentProvider(const service::IResourceService&,
										 const systelab::json::IJSONAdapter&);
			virtual ~RemoteSchemaDocumentProvider() = default;

			std::unique_ptr<systelab::json::IJSONDocument> getRemoteSchemaDocument(const std::string& uri) const;

		private:
			const service::IResourceService& m_resourceService;
			const systelab::json::IJSONAdapter& m_jsonAdapter;
		};

	public:
		JSONValidatorService(const service::IResourceService&,
							 const systelab::json::IJSONAdapter&);
		virtual ~JSONValidatorService() = default;

		void validate(const systelab::json::IJSONDocument&, const std::string& schemaName) const;

	private:
		const systelab::json::IJSONAdapter& m_jsonAdapter;
		std::unique_ptr<RemoteSchemaDocumentProvider> m_documentProvider;
	};

}}

