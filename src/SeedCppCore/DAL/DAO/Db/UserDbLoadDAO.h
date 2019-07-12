#pragma once

#include "EntityDbLoadDAO.h"
#include "Model/User.h"
#include "Model/UserMgr.h"

namespace seed_cpp { namespace dal {

	class UserDbLoadDAO : public EntityDbLoadDAO<model::User, model::UserMgr> { using EntityDbLoadDAO::EntityDbLoadDAO; };

}}
