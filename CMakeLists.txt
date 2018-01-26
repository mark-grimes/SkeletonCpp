#
# CMake file to build REPLACEME_PROJECT_NAME.
# Mark Grimes (mark.grimes@rymapt.com)
# 06/Oct/2017
# copyright 2017 Rymapt Ltd
# Licence to be decided
#

project( REPLACEME_PROJECT_NAME )

cmake_minimum_required(VERSION 2.8)

if( NOT MSVC ) # Microsoft Visual Studio is C++11 by default and doesn't recognise this flag
	add_definitions( "-std=c++11" )
endif()


# Create the file that has the version information and git hash
execute_process( COMMAND git describe --dirty --always --tags WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE REPLACEME_PROJECT_NAME_GIT_DESCRIBE OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process( COMMAND git log -1 --pretty=format:%H WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE REPLACEME_PROJECT_NAME_GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE )
add_custom_target( CreateVersionFile ALL ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/src/version.cpp.in" ) # Make sure the git hash is always checked (not just at configure time)
configure_file( "${CMAKE_SOURCE_DIR}/src/version.cpp.in" "${CMAKE_BINARY_DIR}/src/version.cpp" )

#
# Dependencies
# TODO - allow overriding of the bundled versions with system versions
#
include_directories( ${CMAKE_SOURCE_DIR}/external/asio/include )
# tell websocketpp to use asio standalone, and full C++11 support instead of boost stand-ins
add_definitions( "-DASIO_STANDALONE -D_WEBSOCKETPP_CPP11_STRICT_ -D_WEBSOCKETPP_CPP11_STL_" )
include_directories( ${CMAKE_SOURCE_DIR}/external/websocketpp )
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

include_directories( "${CMAKE_SOURCE_DIR}/include" )
aux_source_directory( "${CMAKE_SOURCE_DIR}/src" library_sources )
list( REMOVE_ITEM library_sources "${CMAKE_SOURCE_DIR}/src/main.cpp" ) # main.cpp belongs only in the executable

add_library( ${PROJECT_NAME}_LIB STATIC ${library_sources} "${CMAKE_BINARY_DIR}/src/version.cpp" )
if( OPENSSL_FOUND )
	target_link_libraries( ${PROJECT_NAME}_LIB ${OPENSSL_LIBRARIES} )
endif()
add_executable( ${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/src/main.cpp" )
target_link_libraries( ${PROJECT_NAME} ${PROJECT_NAME}_LIB )
## Uncomment this if you get "undefined reference to `pthread_create'" when using std::thread
#if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
#	target_link_libraries( ${PROJECT_NAME}_LIB "pthread" )
#endif()

install( TARGETS ${PROJECT_NAME}_LIB DESTINATION lib )
install( DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION include )

option( BUILD_UNITTESTS "Build unit tests" ON )
message( STATUS "BUILD_UNITTESTS: ${BUILD_UNITTESTS}" )
if( BUILD_UNITTESTS )
	# Fix the test configuration file to have the correct paths
	configure_file( "${PROJECT_SOURCE_DIR}/tests/src/testinputs.cpp.in" "${PROJECT_BINARY_DIR}/tests/src/testinputs.cpp" @ONLY )
	include_directories( "${CMAKE_SOURCE_DIR}/tests/include" )
	aux_source_directory( "${CMAKE_SOURCE_DIR}/tests/src" unittests_sources )
	add_executable( ${PROJECT_NAME}Tests ${unittests_sources} "${PROJECT_BINARY_DIR}/tests/src/testinputs.cpp" )
	target_link_libraries( ${PROJECT_NAME}Tests ${PROJECT_NAME}_LIB )
	if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
		target_link_libraries( ${PROJECT_NAME}Tests "pthread" )
	endif()
endif()
