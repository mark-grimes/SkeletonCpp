#include <iostream>
#include "REPLACEME_PROJECT_NAMESPACE/SomeClass.h"
#include "REPLACEME_PROJECT_NAMESPACE/version.h"

int main( int argc, char* argv[] )
{
	std::cout << "SkeletonCpp program with version " << REPLACEME_PROJECT_NAMESPACE::version::GitDescribe << "\n";
	REPLACEME_PROJECT_NAMESPACE::SomeClass instance;
	std::cout << "SomeClass::someValue returns '" << instance.someValue() << "'\n";
	return 0;
}
