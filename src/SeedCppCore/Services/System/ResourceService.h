#pragma once

#include "IResourceService.h"


namespace seed_cpp { namespace service {

	class ResourceService : public IResourceService
	{
	public:
		ResourceService();
		virtual ~ResourceService();

		// Endpoint schemas
		static const std::string schemaPath;
		static const std::string schemaPatientPost;
		static const std::string schemaPatientPut;
		static const std::string schemaUserPost;
		static const std::string schemaUserPut;
		static const std::string schemaAllergyPost;
		static const std::string schemaAllergyPut;

		// Model schemas
		static const std::string schemaModelPatient;
		static const std::string schemaModelAddress;
		static const std::string schemaModelUser;
		static const std::string schemaModelAllergy;

		std::string loadResourceAsString(unsigned int resourceId,
										 const std::string &resourceType) const;

		std::string loadResourceAsString(const std::string &resourceId,
										 const std::string &resourceType) const;

	private:
		bool LoadSchema(const std::string &file);

		std::map<const std::string, std::string> schemas_;
		std::string getSystemErrorMessage() const;
	};

}}
