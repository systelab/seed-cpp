#pragma once

#include "SeedCppCore/DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "SeedCppCore/DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "SeedCppCore/Model/User.h"


namespace seed_cpp { namespace dal {

	class UserJSONSaveTranslator : public IJSONSaveTranslator
	{
	public:
		UserJSONSaveTranslator(const model::User&);
		virtual ~UserJSONSaveTranslator();

		void saveEntityToJSON(systelab::json::IJSONValue&) const;

	protected:
		std::string translateRoleToString(model::User::Role) const;

	private:
		const model::User& m_user;
	};


	class UserJSONLoadTranslator : public IJSONLoadTranslator
	{
	public:
		UserJSONLoadTranslator(model::User&);
		virtual ~UserJSONLoadTranslator();

		void loadEntityFromJSON(const systelab::json::IJSONValue&);

	protected:
		model::User::Role translateStringToRole(const std::string&) const;

	protected:
		model::User& m_user;
	};

}}

