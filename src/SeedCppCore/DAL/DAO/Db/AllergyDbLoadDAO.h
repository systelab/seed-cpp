#pragma once

#include "EntityDbLoadDAO.h"
#include "Model/Allergy.h"
#include "Model/AllergyMgr.h"

namespace seed_cpp { namespace dal {

	class AllergyDbLoadDAO : public EntityDbLoadDAO<model::Allergy, model::AllergyMgr> { using EntityDbLoadDAO::EntityDbLoadDAO; };

}}