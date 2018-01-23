# SkeletonCpp

Creates a skeleton C++ project that builds using CMake. I just got tired of the hassle involved in creating a new project.

## Branches

There are currently two branches

* `master` Is a basic C++ project with [cmake](https://cmake.org) setup and tests using [catch.hpp](https://github.com/catchorg/Catch2).
It is set up to include the git tag and hash in the build, so that you can for example display the git tag with a "-v"
command line.
* `websockets` Has everything from `master` but adds [WebSocket++](https://www.zaphoyd.com/websocketpp) to create web
services. WebSocket++ and ASIO are included directly in the repository so you don't need other dependencies, although
if you don't have OpenSSL you won't be able to use encrypted websockets.

## Usage

Clone the project and then run the `createProject.sh` script. Add your own source files etcetera. You'll probably want
to remove the git history and start again as though it were a fresh git project. E.g. to create a project called FooBar:

```
git clone https://github.com/mark-grimes/SkeletonCpp.git FooBar
cd FooBar
./createProject.sh FooBar
<replace README.md, include/foobar/SomeClass.h, src/SomeClass.cpp and tests/src/test_SomeClass.cpp with your own files>
rm -rf .git ./createProject.sh
git init
git add .
git commit -m "Initial commit of project files"
```

Then to build the project and run your tests

```
mkdir build
cd build
cmake ..
make && ./FooBarTests
```
