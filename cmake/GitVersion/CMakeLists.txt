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
# CMake file to inject git version information into source files
#
# Called from projects with "add_custom_target( cmake <this directory> ... )" so that it is always
# run, since the git version can change without dependencies being out of date.
#
# Probably a divergence of cmake best practices, but it's difficult to get cmake to check the git
# version when the input source hasn't changed.
#
# Mark Grimes (mark.grimes@rymapt.com)
# 29/Mar/2019
# Copyright 2019 Mark Grimes
# Released under the MIT Licence (this file only, other project files may differ)
#
# The canonical location of this file is
# https://github.com/mark-grimes/SkeletonCpp/blob/master/cmake/GitVersion/CMakeLists.txt
#

cmake_minimum_required( VERSION 2.8 )

project( GetGitVersion )

if( NOT input_config_file )
	message( FATAL_ERROR "The variable 'input_config_file' was not set" )
endif()
if( NOT output_configured_file )
	message( FATAL_ERROR "The variable 'output_configured_file' was not set" )
endif()
if( NOT git_directory )
	set( git_directory "${CMAKE_SOURCE_DIR}" )
	message( WARNING "The variable 'git_directory' was not set, defaulting to \"${git_directory}\"" )
endif()
# Don't mind if ${variable_prefix} is not defined, it can be empty.

execute_process( COMMAND git describe --dirty --always --tags WORKING_DIRECTORY ${git_directory} OUTPUT_VARIABLE ${variable_prefix}GIT_DESCRIBE OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process( COMMAND git log -1 --pretty=format:%H WORKING_DIRECTORY ${git_directory} OUTPUT_VARIABLE ${variable_prefix}GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process( COMMAND git log -1 --pretty=format:%h WORKING_DIRECTORY ${git_directory} OUTPUT_VARIABLE ${variable_prefix}GIT_SHORT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE )
configure_file( "${input_config_file}" "${output_configured_file}" )
