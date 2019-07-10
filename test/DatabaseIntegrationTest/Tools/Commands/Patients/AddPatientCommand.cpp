#include "stdafx.h"
#include "AddPatientCommand.h"

#include "DatabaseIntegrationTest/Tools/Core.h"

#include "SeedCppCore/Model/Patient.h"
#include "SeedCppCore/Model/PatientMgr.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelServicesMgr.h"
#include "SeedCppCore/Services/Model/IPatientModelService.h"


namespace seed_cpp { namespace db_test {

	AddPatientCommand::AddPatientCommand(const model::Patient& patient)
		:m_patient(std::make_unique<model::Patient>(patient))
	{
	}

	AddPatientCommand::~AddPatientCommand() = default;

	void AddPatientCommand::execute(Core& core)
	{
		auto& service = core.getServicesMgr().getModelServicesMgr().getPatientModelService();
		auto writeLock = service.createWriteLock();
		service.addEntity(std::move(m_patient), *writeLock);
	}

	std::unique_ptr<ICommand> AddPatientCommand::clone()
	{
		return std::make_unique<AddPatientCommand>(*m_patient);
	}

}}
