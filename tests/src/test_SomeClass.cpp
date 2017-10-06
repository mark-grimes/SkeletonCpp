#include "REPLACEME_PROJECT_NAMESPACE/SomeClass.h"
#include "catch.hpp"

SCENARIO( "Test that REPLACEME_PROJECT_NAMESPACE/SomeClass gives the correct values", "[SomeClass]" )
{
	GIVEN( "An instance of SomeClass" )
	{
		REPLACEME_PROJECT_NAMESPACE::SomeClass anInstance;

		WHEN( "Testing the result of someResult" )
		{
			CHECK( anInstance.someValue() == "It Works!" );
		}
	} // end of 'GIVEN "An instance of SomeClass"'
} // end of 'SCENARIO ... SomeClass'
