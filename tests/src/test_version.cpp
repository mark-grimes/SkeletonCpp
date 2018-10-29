/*
 * Copyright 2018 Mark Grimes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file
 * @brief Tests to make sure the version strings are calculated properly.
 *
 * The canonical location of this file is
 * https://github.com/mark-grimes/SkeletonCpp/blob/master/tests/src/test_version.cpp
 *
 * @author Mark Grimes
 * @copyright Copyright 2018 Mark Grimes. Released under the MIT licence.
 */
#include "REPLACEME_PROJECT_NAMESPACE/version.h"
#include <string>
#include "catch.hpp"

// Use the unnamed namespace for things only used in this file
namespace
{
	bool isHexChar( char character )
	{
		return (character == '0') || (character == '1') || (character == '2') || (character == '3') || (character == '4')
		    || (character == '5') || (character == '6') || (character == '7') || (character == '8') || (character == '9')
		    || (character == 'a') || (character == 'b') || (character == 'c') || (character == 'd') || (character == 'e') || (character == 'f')
		    || (character == 'A') || (character == 'B') || (character == 'C') || (character == 'D') || (character == 'E') || (character == 'F');
	}
} // end of the unnamed namespace

SCENARIO( "Test that REPLACEME_PROJECT_NAMESPACE::version gives the correct git information", "[version]" )
{
	WHEN( "Test there are non zero values for the git hash and git describe" )
	{
		CHECK( REPLACEME_PROJECT_NAMESPACE::version::GitDescribe != nullptr );
		CHECK( std::char_traits<char>::length(REPLACEME_PROJECT_NAMESPACE::version::GitDescribe) > 0 ); // Not sure how to check this consistently
		CHECK( REPLACEME_PROJECT_NAMESPACE::version::GitHash[40] == 0 );
		CHECK( std::char_traits<char>::length(REPLACEME_PROJECT_NAMESPACE::version::GitHash) == 40 ); // Check there are no nulls half way through
		CHECK( REPLACEME_PROJECT_NAMESPACE::version::GitShortHash[7] == 0 );
		CHECK( std::char_traits<char>::length(REPLACEME_PROJECT_NAMESPACE::version::GitShortHash) == 7 ); // Check there are no nulls half way through
	}
	WHEN( "Checking the git hash is all valid hex characters" )
	{
		size_t index;
		for( index=0; index<40; ++index )
		{
			if( !isHexChar(REPLACEME_PROJECT_NAMESPACE::version::GitHash[index]) ) break;
		}
		INFO( std::string("The git hash '")+REPLACEME_PROJECT_NAMESPACE::version::GitHash+"' is not valid hex characters" );
		CHECK( index == 40 ); // make sure the loop completed all the way
	} // end of WHEN checking all characters are hex
	WHEN( "Checking the git short hash is all valid hex characters" )
	{
		size_t index;
		for( index=0; index<7; ++index )
		{
			if( !isHexChar(REPLACEME_PROJECT_NAMESPACE::version::GitShortHash[index]) ) break;
		}
		INFO( std::string("The git hash '")+REPLACEME_PROJECT_NAMESPACE::version::GitShortHash+"' is not valid hex characters" );
		CHECK( index == 7 ); // make sure the loop completed all the way
	} // end of WHEN checking all characters are hex
} // end of 'SCENARIO ... version'
