#include "stdafx.h"
#include "AgentsFactory.h"

#include "Context.h"
#include "Model/Settings.h"

#include "TraceAPI/FileAgent.h"

#include "JSONSettings/SettingsService.h"
#include "JSONSettings/SettingsMacros.h"


namespace seed_cpp { namespace agent {

	AgentsFactory::AgentsFactory(Context& context)
		:m_context(context)
	{
	}
	
	AgentsFactory::~AgentsFactory() = default;

	std::unique_ptr<systelab::trace::IFileAgent> AgentsFactory::buildTraceAgent(const std::string& channelName) const
	{
		systelab::setting::SettingsService settingsService;

		std::string filename = channelName;
		std::string folderPath = GET_JSON_SETTING_STR(settingsService, model::setting::ApplicationSettingsFile, TraceFolderPath);
		unsigned int nArchivedTraceFiles = GET_JSON_SETTING_INT(settingsService, model::setting::ApplicationSettingsFile, TraceMaxArchiveDays);

		return std::make_unique<systelab::trace::FileAgent>(channelName, filename, folderPath, nArchivedTraceFiles);
	}

}}

