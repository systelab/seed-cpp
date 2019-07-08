#include "stdafx.h"
#include "SeedCppCore/Model/Address.h"


namespace seed_cpp { namespace test_utility {

	class AddressBuilder
	{
	public:
		AddressBuilder();
		virtual ~AddressBuilder();

		AddressBuilder& setId(const boost::optional<unsigned int>&);
		AddressBuilder& setCoordinates(const std::string&);
		AddressBuilder& setStreet(const std::string&);
		AddressBuilder& setCity(const std::string&);
		AddressBuilder& setZip(const std::string&);

		model::Address getEntity() const;

	private:
		model::Address m_address;
	};

}}
