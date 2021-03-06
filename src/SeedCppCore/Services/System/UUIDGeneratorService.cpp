#include "stdafx.h"
#include "UUIDGeneratorService.h"


namespace seed_cpp { namespace service {

	UUIDGeneratorService::UUIDGeneratorService()
	{
	}

	UUIDGeneratorService::~UUIDGeneratorService()
	{
	}

	std::string UUIDGeneratorService::generateUUID() const
	{
		boost::uuids::uuid newUUID = m_generator();
		return boost::uuids::to_string(newUUID);
	}

}}
