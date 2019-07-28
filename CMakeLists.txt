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
# CMake file to build REPLACEME_PROJECT_NAME.
# Mark Grimes (mark.grimes@rymapt.com)
# 06/Oct/2017
# Copyright 2019 Mark Grimes
# Released under the MIT Licence (this file only, other project files may differ)
#
# The canonical location of this file is
# https://github.com/mark-grimes/SkeletonCpp/blob/master/CMakeLists.txt
#

project( REPLACEME_PROJECT_NAME )

cmake_minimum_required(VERSION 2.8)

if( NOT MSVC ) # Microsoft Visual Studio is C++11 by default and doesn't recognise this flag
	add_definitions( "-std=c++11" )
endif()


# Create the file that has the version information and git hash
file( MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/REPLACEME_PROJECT_NAME_CreateVersionFileDir" )
add_custom_target( REPLACEME_PROJECT_NAME_CreateVersionFile
					COMMAND ${CMAKE_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GitVersion"
						"-Dinput_config_file=${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp.in"
						"-Doutput_configured_file=${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp"
						"-Dgit_directory=${CMAKE_CURRENT_SOURCE_DIR}"
						"-Dvariable_prefix=REPLACEME_PROJECT_NAME_"
					WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/REPLACEME_PROJECT_NAME_CreateVersionFileDir"
					DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp.in" )
add_custom_command( OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp"
					DEPENDS REPLACEME_PROJECT_NAME_CreateVersionFile )

# Add any source files to this list
set( REPLACEME_PROJECT_NAME_library_sources
		"${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp" ) # Generated file containing the git hash
add_library( REPLACEME_PROJECT_NAMECore STATIC ${REPLACEME_PROJECT_NAME_library_sources} )
target_include_directories( REPLACEME_PROJECT_NAMECore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
## Uncomment this if you get "undefined reference to `pthread_create'" when using std::thread
#if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
#	target_link_libraries( REPLACEME_PROJECT_NAMECore "pthread" )
#endif()

add_executable( REPLACEME_PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" )
target_link_libraries( REPLACEME_PROJECT_NAME REPLACEME_PROJECT_NAMECore )

install( TARGETS REPLACEME_PROJECT_NAMECore DESTINATION lib )
install( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include )

option( BUILD_UNITTESTS "Build unit tests" ON )
option( BUILD_DOCS "Build API documentation" OFF )
message( STATUS "BUILD_UNITTESTS: ${BUILD_UNITTESTS}" )
message( STATUS "BUILD_DOCS:      ${BUILD_DOCS}" )

if( BUILD_UNITTESTS )
	add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests )
endif()

if( BUILD_DOCS )
	add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/docs )
endif()
