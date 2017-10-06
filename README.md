# SkeletonCpp

Creates a skeleton C++ project that builds using CMake. I just got tired of the hassle involved in creating a new project.

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