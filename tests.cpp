#include "stdafx.h"

#include "UnitTest++/UnitTest++.h"

// entry point for running tests
// this file is excluded in build/release, only included in the tests config
int main() {

	printf("Suite: %s\n", UnitTestSuite::GetSuiteName());
	UnitTest::RunAllTests();
}