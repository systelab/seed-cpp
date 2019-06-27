#pragma once

namespace seed_cpp { namespace model {

	class AllergyMgr;
	class PatientMgr;
	class UserMgr;

	class Model
	{
	public:
		Model();
		Model(const Model&);
		virtual ~Model();

		AllergyMgr& getAllergyMgr() const;
		PatientMgr& getPatientMgr() const;
		UserMgr& getUserMgr() const;

		Model& operator= (const Model&);

	private:
		std::unique_ptr<AllergyMgr> m_allergyMgr;
		std::unique_ptr<PatientMgr> m_patientMgr;
		std::unique_ptr<UserMgr> m_userMgr;
	};

}}
