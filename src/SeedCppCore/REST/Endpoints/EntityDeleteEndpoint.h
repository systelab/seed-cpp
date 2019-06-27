#pragma once

#include "IEndpoint.h"

#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "WebServerAdapterInterface/Model/Reply.h"
#include "WebServerAdapterInterface/Model/RequestHeaders.h"

namespace seed_cpp { namespace rest {
	
	template <typename _EntityModelService>
	class EntityDeleteEndpoint : public IEndpoint
	{
	public:
		EntityDeleteEndpoint(const systelab::web_server::RequestHeaders& headers,
							 const std::string& entityId,
							 _EntityModelService& entityModelService,
							 const service::IAuthorizationValidatorService& authorizationValidatorService)
			:m_headers(headers)
			,m_entityId(entityId)
			,m_entityModelService(entityModelService)
			,m_authorizationValidatorService(authorizationValidatorService)
		{
		}

		virtual ~EntityDeleteEndpoint() = default;

		bool hasAccess() const override
		{
			return m_authorizationValidatorService.validate(m_headers);
		}

		std::unique_ptr<systelab::web_server::Reply> execute() override
		{
			auto lock = m_entityModelService.createWriteLock();
			const auto entity = m_entityModelService.getEntityById(m_entityId, *lock);
			if (!entity)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
			}

			try
			{
				m_entityModelService.deleteEntity(m_entityId, *lock);
				return ReplyBuilderHelper::build(systelab::web_server::Reply::NO_CONTENT);
			}
			catch (std::exception& exc)
			{
				return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
			}
		}

	private:
		const systelab::web_server::RequestHeaders m_headers;
		const std::string m_entityId;
		_EntityModelService& m_entityModelService;
		const service::IAuthorizationValidatorService& m_authorizationValidatorService;
	};

}}