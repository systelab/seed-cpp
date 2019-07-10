#include "stdafx.h"
#include "DeletePatientCommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"

#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelServicesMgr.h"
#include "SeedCppCore/Services/Model/IPatientModelService.h"


namespace seed_cpp { namespace db_test {

	DeletePatientCommand::DeletePatientCommand(const std::string& patientId)
		:m_patientId(patientId)
	{
	}

	DeletePatientCommand::~DeletePatientCommand() = default;

	void DeletePatientCommand::execute(Core& core)
	{
		auto& service = core.getServicesMgr().getModelServicesMgr().getPatientModelService();
		auto writeLock = service.createWriteLock();
		service.deleteEntity(m_patientId, *writeLock);
	}

	std::unique_ptr<ICommand> DeletePatientCommand::clone()
	{
		return std::make_unique<DeletePatientCommand>(m_patientId);
	}

}}

