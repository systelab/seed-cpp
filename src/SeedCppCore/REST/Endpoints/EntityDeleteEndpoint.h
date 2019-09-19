#pragma once

#include "SeedCppCore/REST/Helpers/ReplyBuilderHelper.h"

#include "RESTAPICore/Endpoint/IEndpoint.h"
#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {
	
	template <typename _EntityModelService>
	class EntityDeleteEndpoint : public systelab::rest_api_core::IEndpoint
	{
	public:
		EntityDeleteEndpoint(_EntityModelService& entityModelService)
			:m_entityModelService(entityModelService)
		{
		}

		virtual ~EntityDeleteEndpoint() = default;

		std::unique_ptr<systelab::web_server::Reply> execute(const systelab::rest_api_core::EndpointRequestData& requestData) override
		{
			std::string entityId = requestData.getParameters().getStringParameter("id");
			auto lock = m_entityModelService.createWriteLock();
			const auto entity = m_entityModelService.getEntityById(entityId, *lock);
			if (!entity)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
			}

			try
			{
				m_entityModelService.deleteEntity(entityId, *lock);
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NO_CONTENT);
			}
			catch (std::exception& exc)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
			}
		}

	private:
		_EntityModelService& m_entityModelService;
	};

}}
