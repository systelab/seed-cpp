from conans import ConanFile, tools

class SeedCppConan(ConanFile):
    name = "SeedCpp"
    description = "Seed for Systelab C++ projects"
    url = "https://github.com/systelab/seed-cpp"
    homepage = "https://github.com/systelab/seed-cpp"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "seed", "cpp", "systelab", "new", "projects")
    license = "MIT"
    generators = "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    options = {"boost": ["1.67.0", "1.72.0", "1.75.0"], "openssl": ["1.1.1g", "1.1.1k"], "gtest": ["1.8.1", "1.10.0"]}
    default_options = {"boost": "1.72.0", "openssl":"1.1.1k", "gtest":"1.10.0"}

    def configure(self):
        self.options["DbSQLiteAdapter"].boost = self.options.boost
        self.options["BoostAsioWebServerAdapter"].boost = self.options.boost
        self.options["BoostAsioWebServerAdapter"].openssl = self.options.openssl
        self.options["JWTUtils"].openssl = self.options.openssl
        self.options["RESTAPICore"].openssl = self.options.openssl
        self.options["JSONSettings"].boost = self.options.boost

        self.options["DbAdapterTestUtilities"].gtest = self.options.gtest
        self.options["JSONAdapterTestUtilities"].gtest = self.options.gtest
        self.options["JWTUtilsTestUtilities"].gtest = self.options.gtest
        self.options["JSONSettingsTestUtilities"].boost = self.options.boost
        self.options["JSONSettingsTestUtilities"].gtest = self.options.gtest

    def requirements(self):
        self.requires("DbSQLiteAdapter/1.1.10@systelab/stable")
        self.requires("RapidJSONAdapter/1.1.3@systelab/stable")
        self.requires("BoostAsioWebServerAdapter/1.1.5@systelab/stable")
        self.requires("JWTUtils/1.1.7@systelab/stable")
        self.requires("RESTAPICore/1.1.7@systelab/stable")
        self.requires("JSONSettings/1.3.8@systelab/stable")
        self.requires("rapidjson/1.1.0.1@systelab/stable")

    def build_requirements(self):
        self.build_requires("TestUtilitiesInterface/1.0.7@systelab/stable")
        self.build_requires("DbAdapterInterface/1.1.12@systelab/stable")
        self.build_requires("DbAdapterTestUtilities/1.1.12@systelab/stable")
        self.build_requires("JSONAdapterInterface/1.1.3@systelab/stable")
        self.build_requires("JSONAdapterTestUtilities/1.1.3@systelab/stable")
        self.build_requires("JWTUtilsTestUtilities/1.1.7@systelab/stable")
        self.build_requires("JSONSettingsTestUtilities/1.3.8@systelab/stable")
        self.build_requires("WebServerAdapterInterface/1.1.10@systelab/stable")
        self.build_requires("gtest/1.10.0")
        
    def imports(self):
        self.copy("*.dll", dst=("bin/SeedCpp/%s" % self.settings.build_type), src="bin")
        self.copy("*.dll", dst=("bin/SeedCppCoreUnitTest/%s" % self.settings.build_type), src="bin")
        self.copy("*.dll", dst=("bin/DatabaseIntegrationTest/%s" % self.settings.build_type), src="bin")
        self.copy("*.dylib*", dst="bin/SeedCpp", src="lib")
        self.copy("*.dylib*", dst="bin/SeedCppCoreUnitTest", src="lib")
        self.copy("*.dylib*", dst="bin/DatabaseIntegrationTest", src="lib")
        self.copy("*.so*", dst="bin/SeedCpp", src="lib")
        self.copy("*.so*", dst="bin/SeedCppCoreUnitTest", src="lib")
        self.copy("*.so*", dst="bin/DatabaseIntegrationTest", src="lib")

    def package(self):
        self.copy("*.exe", dst="bin", src="bin/SeedCpp")
        self.copy("*.dll", dst="bin", src="bin/SeedCpp")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
