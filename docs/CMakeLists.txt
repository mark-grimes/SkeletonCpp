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
# CMake file to build the documentation for REPLACEME_PROJECT_NAME.
# Mark Grimes (mark.grimes@rymapt.com)
# 02/Oct/2018
# Copyright 2018 Mark Grimes
# Released under the MIT Licence
#
# The canonical location of this file is
# https://github.com/mark-grimes/SkeletonCpp/blob/master/doc/CMakeLists.txt
#

find_package( Doxygen QUIET )
if( NOT DOXYGEN_FOUND )
	message( WARNING "Doxygen was not found. If you have it in a non standard location try setting DOXYGEN_EXECUTABLE manually." )
	add_custom_target( docs ${CMAKE_COMMAND} -E echo "The docs target cannot be built because doxygen was not found" )
else()
	# Need to replace "DOXYGEN_INPUT" in the Doxygen file with the actual path to the sources
	get_filename_component( DOXYGEN_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/../include" REALPATH )
	configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" )
	add_custom_target( docs ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )
endif()
