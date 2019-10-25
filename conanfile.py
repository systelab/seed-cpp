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
    options = {"boost": ["1.67.0"], "OpenSSL": ["1.0.2n"], "gtest": ["1.8.1"]}
    default_options = {"boost": "1.67.0", "OpenSSL":"1.0.2n", "gtest":"1.8.1"}

    def configure(self):
        self.options["DbSQLiteAdapter"].boost = self.options.boost
        self.options["BoostAsioWebServerAdapter"].boost = self.options.boost
        self.options["BoostAsioWebServerAdapter"].OpenSSL = self.options.OpenSSL
        self.options["JWTUtils"].OpenSSL = self.options.OpenSSL
        self.options["RESTAPICore"].OpenSSL = self.options.OpenSSL

    def requirements(self):
        self.requires("DbSQLiteAdapter/1.1.5@systelab/stable")
        self.requires("RapidJSONAdapter/1.0.3@systelab/stable")
        self.requires("BoostAsioWebServerAdapter/1.0.2@systelab/stable")
        self.requires("JWTUtils/1.0.3@systelab/stable")
        self.requires("RESTAPICore/1.0.2@systelab/stable")

    def build_requirements(self):
        self.build_requires("TestUtilitiesInterface/1.0.3@systelab/stable")
        if self.options.gtest == "1.7.0":
            self.build_requires("gtest/1.7.0@systelab/stable")
        else:
            self.build_requires("gtest/1.8.1@bincrafters/stable")

    def imports(self):
        self.copy("*.dll", dst=("bin/%s" % self.settings.build_type), src="bin")
        self.copy("*.dylib*", dst=("bin/%s" % self.settings.build_type), src="lib")
        self.copy("*.so*", dst=("bin/%s" % self.settings.build_type), src="lib")

    def package(self):
        self.copy("*.exe", dst="bin", src="bin/SeedCpp")
        self.copy("*.dll", dst="bin", src="bin/SeedCpp")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
