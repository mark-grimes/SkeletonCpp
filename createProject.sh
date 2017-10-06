#! /bin/bash
#
# Creates a C++ cmake project with test directory etcetera
# Mark Grimes 06/Oct/2017
# copyright Mark Grimes 2017
# Released under the MIT licence (see https://opensource.org/licenses/MIT)
#

REPLACEME_PROJECT_NAME="FooBar"
REPLACEME_PROJECT_NAMESPACE="foobar"
REPLACEME_PROJECT_TESTS_NAMESPACE="${REPLACEME_PROJECT_NAMESPACE}tests"

mv "include/REPLACEME_PROJECT_NAMESPACE" "include/${REPLACEME_PROJECT_NAMESPACE}"
mv "tests/include/REPLACEME_PROJECT_TESTS_NAMESPACE" "tests/include/${REPLACEME_PROJECT_TESTS_NAMESPACE}"
sed -i -e s:"REPLACEME_PROJECT_NAMESPACE":"${REPLACEME_PROJECT_NAMESPACE}":g \
       -e s:"REPLACEME_PROJECT_NAME":"${REPLACEME_PROJECT_NAME}":g \
       -e s:"REPLACEME_PROJECT_TESTS_NAMESPACE":"${REPLACEME_PROJECT_TESTS_NAMESPACE}":g \
           "tests/include/${REPLACEME_PROJECT_TESTS_NAMESPACE}/testinputs.h" \
           "tests/src/testinputs.cpp.in" \
           "tests/src/test_SomeClass.cpp" \
           "include/${REPLACEME_PROJECT_NAMESPACE}/SomeClass.h" \
           "src/SomeClass.cpp" \
           "CMakeLists.txt"
