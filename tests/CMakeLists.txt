#
# Copyright 2019 Mark Grimes
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
# OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

#
# CMake file to build tests for REPLACEME_PROJECT_NAME.
# Mark Grimes (mark.grimes@rymapt.com)
# 25/Oct/2018
# Copyright 2019 Mark Grimes.
# Released under the MIT Licence (this file only, other project files may differ)
#
# The canonical location of this file is
# https://github.com/mark-grimes/SkeletonCpp/blob/master/tests/CMakeLists.txt
#


# Fix the test configuration file to have the correct paths
configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/testinputs.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/src/testinputs.cpp" @ONLY )

# Compile all the test sources into an executable test runner
set( REPLACEME_PROJECT_NAME_unittests_sources
	src/test_version.cpp
	"${CMAKE_CURRENT_BINARY_DIR}/src/testinputs.cpp"  # Generated file with directory locations of the test data
	src/main.cpp )
add_executable( REPLACEME_PROJECT_NAMETests ${REPLACEME_PROJECT_NAME_unittests_sources} )
target_include_directories( REPLACEME_PROJECT_NAMETests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" )
target_link_libraries( REPLACEME_PROJECT_NAMETests REPLACEME_PROJECT_NAME_LIB )
