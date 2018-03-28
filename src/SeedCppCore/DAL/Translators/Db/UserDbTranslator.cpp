#include "StdAfx.h"
#include "UserDbTranslator.h"

#include "Model/User.h"

#include "DbAdapterInterface/ITableRecord.h"
#include "DbAdapterInterface/IFieldValue.h"


namespace seed_cpp { namespace dal {

	UserDbTranslator::UserDbTranslator(model::User& user)
		:m_user(user)
	{
	}

	UserDbTranslator::~UserDbTranslator()
	{
	}

	void UserDbTranslator::fillEntityFromRecord(const systelab::db::ITableRecord& record)
	{
		unsigned int id = record.getFieldValue("id").getIntValue();
		std::string name = record.getFieldValue("name").getStringValue();
		std::string surname = record.getFieldValue("surname").getStringValue();
		std::string login = record.getFieldValue("login").getStringValue();
		std::string password = record.getFieldValue("password").getStringValue();
		model::User::Role role = (model::User::Role) record.getFieldValue("role").getIntValue();

		m_user.setId(id);
		m_user.setName(name);
		m_user.setSurname(surname);
		m_user.setLogin(login);
		m_user.setPassword(password);
		m_user.setRole(role);
	}

	void UserDbTranslator::fillRecordFromEntity(systelab::db::ITableRecord& record) const
	{
		boost::optional<unsigned int> id = m_user.getId();
		if (id)
		{
			record.getFieldValue("id").setIntValue((int) *id);
		}
		else
		{
			record.getFieldValue("id").setDefault();
		}

		std::string name = m_user.getName();
		std::string surname = m_user.getSurname();
		std::string login = m_user.getLogin();
		std::string password = m_user.getPassword();
		int role = (int) m_user.getRole();

		record.getFieldValue("name").setStringValue(name);
		record.getFieldValue("surname").setStringValue(surname);
		record.getFieldValue("login").setStringValue(login);
		record.getFieldValue("password").setStringValue(password);
		record.getFieldValue("role").setIntValue(role);
	}

}}
