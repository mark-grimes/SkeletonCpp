#! /bin/sh
#
# Creates a C++ cmake project with test directory etcetera
# Mark Grimes 06/Oct/2017
# copyright Mark Grimes 2019
# Released under the MIT licence (see https://opensource.org/licenses/MIT)
#

if [ $# -ne 1 ] && [ $# -ne 2 ]; then
	echo "You should specify the project name as the first argument. Don't use spaces or it'll probably end in tears. Optionally also specify the namespace as the second argument." >&2
	exit
fi

REPLACEME_PROJECT_NAME="$1"
if [ $# -gt 1 ]; then
	REPLACEME_PROJECT_NAMESPACE="$2"
else
	# Convert project name to lower case
	REPLACEME_PROJECT_NAMESPACE=`echo ${REPLACEME_PROJECT_NAME} | tr '[:upper:]' '[:lower:]'`
fi
REPLACEME_PROJECT_TESTS_NAMESPACE="${REPLACEME_PROJECT_NAMESPACE}tests"

mv "include/REPLACEME_PROJECT_NAMESPACE" "include/${REPLACEME_PROJECT_NAMESPACE}"
mv "tests/include/REPLACEME_PROJECT_TESTS_NAMESPACE" "tests/include/${REPLACEME_PROJECT_TESTS_NAMESPACE}"

# Need to figure out if the sed version needs arguments changed. Sed on OS X is quite different.
# The only difference between the two commands is whether or not there are empty quotes after the
# '-i' option.
if sed -i -e s:"duMmy":"duMmy": -e s:"duMmy":"duMmy": CMakeLists.txt 2>/dev/null; then
	# Normal version of sed
	sed -i -e s:"REPLACEME_PROJECT_NAMESPACE":"${REPLACEME_PROJECT_NAMESPACE}":g \
	       -e s:"REPLACEME_PROJECT_NAME":"${REPLACEME_PROJECT_NAME}":g \
	       -e s:"REPLACEME_PROJECT_TESTS_NAMESPACE":"${REPLACEME_PROJECT_TESTS_NAMESPACE}":g \
	            "tests/include/${REPLACEME_PROJECT_TESTS_NAMESPACE}/testinputs.h" \
	            "tests/src/testinputs.cpp.in" \
	            "include/${REPLACEME_PROJECT_NAMESPACE}/version.h" \
	            "src/version.cpp.in" \
	            "tests/src/test_version.cpp" \
	            "src/main.cpp" \
	            "docs/CMakeLists.txt" \
	            "docs/Doxyfile.in" \
	            "tests/CMakeLists.txt" \
	            "CMakeLists.txt"
else
	# Probably Mac OS X
	sed -i "" -e s:"REPLACEME_PROJECT_NAMESPACE":"${REPLACEME_PROJECT_NAMESPACE}":g \
	          -e s:"REPLACEME_PROJECT_NAME":"${REPLACEME_PROJECT_NAME}":g \
	          -e s:"REPLACEME_PROJECT_TESTS_NAMESPACE":"${REPLACEME_PROJECT_TESTS_NAMESPACE}":g \
	               "tests/include/${REPLACEME_PROJECT_TESTS_NAMESPACE}/testinputs.h" \
	               "tests/src/testinputs.cpp.in" \
	               "include/${REPLACEME_PROJECT_NAMESPACE}/version.h" \
	               "src/version.cpp.in" \
	               "tests/src/test_version.cpp" \
	               "src/main.cpp" \
	               "docs/CMakeLists.txt" \
	               "docs/Doxyfile.in" \
	               "tests/CMakeLists.txt" \
	               "CMakeLists.txt"
fi
