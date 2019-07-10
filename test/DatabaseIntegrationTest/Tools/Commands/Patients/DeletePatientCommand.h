#pragma once

#include "Tools/Commands/ICommand.h"


namespace seed_cpp { namespace model {
	class Patient;
}}

namespace seed_cpp { namespace db_test {

	class DeletePatientCommand : public ICommand
	{
	public:
		DeletePatientCommand(const std::string&);
		virtual ~DeletePatientCommand();

		void execute(Core&) override;
		std::unique_ptr<ICommand> clone() override;

	protected:
		std::string m_patientId;
	};

}}
