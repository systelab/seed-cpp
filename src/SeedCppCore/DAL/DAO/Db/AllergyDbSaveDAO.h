#pragma once

#include "EntityDbSaveDAO.h"
#include "Model/Allergy.h"

namespace seed_cpp { namespace dal {

	class AllergyDbSaveDAO : public EntityDbSaveDAO<model::Allergy> { using EntityDbSaveDAO::EntityDbSaveDAO; };

}}