#include "stdafx.h"
#include "DatabaseTranslatorTest.h"

#include "SeedCppCore/DAL/Translators/Db/AddressDbTranslator.h"
#include "SeedCppCore/Model/Address.h"


using namespace systelab::db::test_utility;

namespace seed_cpp { namespace unit_test {

	struct Address1Wrapper
	{
		typedef model::Address ModelEntity;

		static model::Address getEntity()
		{
			model::Address address;
			address.setId(123);
			address.setCoordinates("N 123.123, E 245,245");
			address.setStreet("C/Major, 17 2n 3a");
			address.setCity("Granollers");
			address.setZip("17246");

			return address;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", 123),
					  StubFieldValue("patientId", std::string("1A4390F4-C0F6-4827-BC2E-1619BBF56AF6")),
					  StubFieldValue("coordinates", std::string("N 123.123, E 245,245")),
					  StubFieldValue("street", std::string("C/Major, 17 2n 3a")),
					  StubFieldValue("city", std::string("Granollers")),
					  StubFieldValue("zip", std::string("17246")),
					};
		}

		static std::unique_ptr<dal::AddressDbTranslator> buildDbTranslator(model::Address& entity)
		{
			std::string patientId = "1A4390F4-C0F6-4827-BC2E-1619BBF56AF6";
			return std::make_unique<dal::AddressDbTranslator>(patientId, entity);
		}
	};

	struct Address2Wrapper
	{
		typedef model::Address ModelEntity;

		static model::Address getEntity()
		{
			model::Address address;
			address.setId(456);
			address.setCoordinates("S 432.324, W 6529.721");
			address.setStreet("Avda. Can Moncau, 7");
			address.setCity("Lliça d'Amunt");
			address.setZip("08080");

			return address;
		}

		static std::vector<StubFieldValue> getRecordData()
		{
			return	{ StubFieldValue("id", 456),
					  StubFieldValue("patientId", std::string("DD4DDA02-9652-48DF-93F6-3461950770F1")),
					  StubFieldValue("coordinates", std::string("S 432.324, W 6529.721")),
					  StubFieldValue("street", std::string("Avda. Can Moncau, 7")),
					  StubFieldValue("city", std::string("Lliça d'Amunt")),
					  StubFieldValue("zip", std::string("08080")),
			};
		}

		static std::unique_ptr<dal::AddressDbTranslator> buildDbTranslator(model::Address& entity)
		{
			std::string patientId = "DD4DDA02-9652-48DF-93F6-3461950770F1";
			return std::make_unique<dal::AddressDbTranslator>(patientId, entity);
		}
	};


	typedef ::testing::Types<
		Address1Wrapper,
		Address2Wrapper
	> AddressDbTranslatorTestWrappers;

	INSTANTIATE_TYPED_TEST_CASE_P(AddressTranslatorTest, DatabaseTranslatorTest, AddressDbTranslatorTestWrappers);

}}