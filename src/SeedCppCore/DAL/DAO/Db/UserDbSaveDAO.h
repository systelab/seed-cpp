#pragma once

#include "DAL/DAO/Db/EntityDbSaveDAO.h"
#include "Model/User.h"


namespace seed_cpp { namespace dal {

	class UserDbSaveDAO : public EntityDbSaveDAO<model::User> { using EntityDbSaveDAO::EntityDbSaveDAO; };

}}

