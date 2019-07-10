#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace db_test {

	class AddPatientCommand : public ICommand
	{
	public:
		AddPatientCommand(const model::Patient&);
		virtual ~AddPatientCommand();

		void execute(Core&) override;
		std::unique_ptr<ICommand> clone() override;

	protected:
		std::unique_ptr<model::Patient> m_patient;
	};

}}