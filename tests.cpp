#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

// entry point for running tests
// this file is excluded in build/release, only included in the tests config
int main() {

	UnitTest::RunAllTests();

	printf("Press enter to continue ...");
	getchar();
}