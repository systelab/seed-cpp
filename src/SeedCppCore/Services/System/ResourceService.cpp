#include "stdafx.h"
#include "ResourceService.h"

#include <fstream>
#include <sstream>
#include <string>

#pragma warning(disable : 4996)


namespace seed_cpp { namespace service {
	
	const std::string ResourceService::schemaPath			= "JSONSchemas/";

	// Endpoint schemas
	const std::string ResourceService::schemaPatientPost	= "Endpoint/PatientsPostEndpoint.json";
	const std::string ResourceService::schemaPatientPut		= "Endpoint/PatientsPutEndpoint.json";
	const std::string ResourceService::schemaUserPost		= "Endpoint/UsersPostEndpoint.json";
	const std::string ResourceService::schemaUserPut		= "Endpoint/UsersPutEndpoint.json";
	const std::string ResourceService::schemaAllergyPost	= "Endpoint/AllergiesPostEndpoint.json";
	const std::string ResourceService::schemaAllergyPut		= "Endpoint/AllergiesPutEndpoint.json";

	// Model schemas
	const std::string ResourceService::schemaModelPatient	= "Model/Patient.json";
	const std::string ResourceService::schemaModelAddress	= "Model/Address.json";
	const std::string ResourceService::schemaModelUser		= "Model/User.json";
	const std::string ResourceService::schemaModelAllergy	= "Model/Allergy.json";

	ResourceService::ResourceService()
	{
		std::map<std::string, std::string> supportedJson =
		{
			// Endpoint Schemas
			{"JSON_SCHEMA_ENDPOINT_PATIENTS_POST",	schemaPatientPost},
			{"JSON_SCHEMA_ENDPOINT_PATIENTS_PUT",	schemaPatientPut},
			{"JSON_SCHEMA_ENDPOINT_USERS_POST",		schemaUserPost},
			{"JSON_SCHEMA_ENDPOINT_USERS_PUT",		schemaUserPut},
			{"JSON_SCHEMA_ENDPOINT_ALLERGIES_POST",	schemaAllergyPost},
			{"JSON_SCHEMA_ENDPOINT_ALLERGIES_PUT",	schemaAllergyPut},

			// Model Schemas
			{"JSON_SCHEMA_MODEL_PATIENT",			schemaModelPatient},
			{"JSON_SCHEMA_MODEL_ADDRESS",			schemaModelAddress},
			{"JSON_SCHEMA_MODEL_USER",				schemaModelUser},
			{"JSON_SCHEMA_MODEL_ALLERGY",			schemaModelAllergy}
		};

		for (auto i : supportedJson)
		{
			std::ifstream t(schemaPath + i.second);
			std::string schema((std::istreambuf_iterator<char>(t)),
								std::istreambuf_iterator<char>());
			schemas_.insert(std::make_pair(i.first, schema));
		}
	}

	ResourceService::~ResourceService() {}

	std::string
	ResourceService::loadResourceAsString(unsigned int resourceId,
										  const std::string &resourceType) const
	{
		(void)resourceId;
		return resourceType;
	}

	std::string
	ResourceService::loadResourceAsString(const std::string &resourceId,
										  const std::string &resourceType) const
	{
		if (resourceType != "JSON_SCHEMA")
		{
			throw std::string("Not Supported resource type!.");
		}

		if (schemas_.count(resourceId) == 1)
		{
			return schemas_.find(resourceId)->second;
		}
		else
		{
			throw std::string("Schema not found!.");
		}
	}

}}
