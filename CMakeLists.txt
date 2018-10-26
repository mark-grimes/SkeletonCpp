#
# Copyright 2018 Mark Grimes
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
# Copyright 2018 Mark Grimes
# Released under the MIT Licence
#
# The canonical location of this file is
# https://github.com/mark-grimes/SkeletonCpp/blob/websockets/CMakeLists.txt
#

project( REPLACEME_PROJECT_NAME )

cmake_minimum_required(VERSION 2.8)

if( NOT MSVC ) # Microsoft Visual Studio is C++11 by default and doesn't recognise this flag
	add_definitions( "-std=c++11" )
endif()


# Create the file that has the version information and git hash
execute_process( COMMAND git describe --dirty --always --tags WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE REPLACEME_PROJECT_NAME_GIT_DESCRIBE OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process( COMMAND git log -1 --pretty=format:%H WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE REPLACEME_PROJECT_NAME_GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE )
add_custom_target( ${PROJECT_NAME}_CreateVersionFile ALL ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp.in" ) # Make sure the git hash is always checked (not just at configure time)
configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp.in" "${PROJECT_BINARY_DIR}/src/version.cpp" )

#
# Dependencies
# TODO - allow overriding of the bundled versions with system versions
#
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/external/asio/include )
# tell websocketpp to use asio standalone, and full C++11 support instead of boost stand-ins
add_definitions( "-DASIO_STANDALONE -D_WEBSOCKETPP_CPP11_STRICT_ -D_WEBSOCKETPP_CPP11_STL_" )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/external/websocketpp )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include )
#
# Find OpenSSL
#
find_package( OpenSSL QUIET )
if( OPENSSL_FOUND )
	include_directories( ${OPENSSL_INCLUDE_DIR} )
	add_definitions( "-DENCRYPTED_WEBSOCKETS_AVAILABLE" )
else()
	message( WARNING "OpenSSL was not found on your system. You will not be able to use encrypted websockets." )
endif()

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/src" ${PROJECT_NAME}_library_sources )
list( REMOVE_ITEM ${PROJECT_NAME}_library_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" ) # main.cpp belongs only in the executable

add_library( ${PROJECT_NAME}_LIB STATIC ${${PROJECT_NAME}_library_sources} "${PROJECT_BINARY_DIR}/src/version.cpp" )
if( OPENSSL_FOUND )
	target_link_libraries( ${PROJECT_NAME}_LIB ${OPENSSL_LIBRARIES} )
endif()
add_executable( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" )
target_link_libraries( ${PROJECT_NAME} ${PROJECT_NAME}_LIB )
## Uncomment this if you get "undefined reference to `pthread_create'" when using std::thread
#if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
#	target_link_libraries( ${PROJECT_NAME}_LIB "pthread" )
#endif()

install( TARGETS ${PROJECT_NAME}_LIB DESTINATION lib )
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
