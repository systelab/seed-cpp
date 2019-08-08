#pragma once

#include "Services/System/IUUIDGeneratorService.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


namespace seed_cpp { namespace service {

	class UUIDGeneratorService : public IUUIDGeneratorService
	{
	public:
		UUIDGeneratorService();
		virtual ~UUIDGeneratorService();

		std::string generateUUID() const;

	private:
		mutable boost::uuids::random_generator m_generator;
	};

}}
