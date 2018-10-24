# seed-cpp — Seed for C++ Systelab projects

This project is an application skeleton for a typical C++ application. You can use it to quickly bootstrap your projects and dev environment.

The seed contains a Patient Management sample Web API.

The app doesn't do much, just shows how to use different C++ patterns and other suggested tools together:

* ...
* ...


## Getting Started

To get you started you can simply clone the `seed-cpp` repository, install the external libraries and build the application.

### Clone `seed-cpp`

Clone the `seed-cpp` repository using git:

```bash
git clone https://github.com/systelab/seed-cpp.git
cd seed-dotnet
```

If you just want to start a new project without the seed-cpp commit history then you can do:

```bash
git clone --depth=1 https://github.com/systelab/seed-cpp.git <your-project-name>
```

The depth=1 tells git to only pull down one commit worth of historical data.


### Build external libraries

Clone the `vcpkg` repository using git:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
```

Then run vcpkg bootstrap batch file:

```bash
.\bootstrap-vcpkg.bat
```

Download and build the following packages (notice that this process may take some minutes):

```bash
.\vcpkg install sqlite3:x64-windows boost-asio:x64-windows boost-date-time:x64-windows boost-uuid:x64-windows rapidjson:x64-windows gtest:x64-windows
```

Pack the generated binaries and includes in a folder:

```bash
.\vcpkg export sqlite3:x64-windows boost-asio:x64-windows boost-date-time:x64-windows boost-uuid:x64-windows rapidjson:x64-windows gtest:x64-windows --raw
```

Move the packed folder generated on the previous step into the `seed-cpp` cloned repository.
Moreover, copy the contents of the subfolder `vcpkg-export-XXXXXXXX-XXXXXX/installed/x64-windows` into `seed-cpp/vcpkg` folder.


### Build the application

TBD

## Run the application

To run the project, ...

### How it works

After login (with username **Systelab** and password **Systelab**), copy the Token returned in the Authorization field before running any other REST endpoint.

[git]: https://git-scm.com/
