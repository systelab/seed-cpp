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

    def requirements(self):
        self.requires("DbSQLiteAdapter/1.1.1@systelab/stable")
        self.requires("RapidJSONAdapter/1.0.1@systelab/stable")
        self.requires("BoostAsioWebServerAdapter/1.0.1@systelab/stable")
        self.requires("JWTUtils/1.0.1@systelab/stable")
        self.requires("RESTAPICore/1.0.0@systelab/stable")

    def imports(self):
        self.copy("*.dll", dst=("lib/extern"), src="bin")
        self.copy("*.dylib*", dst=("lib/extern"), src="lib")
        self.copy("*.so*", dst=("lib/extern"), src="lib")

    def package(self):
        self.copy("*.exe", dst="bin", src="bin/SeedCpp")
        self.copy("*.dll", dst="bin", src="bin/SeedCpp")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
