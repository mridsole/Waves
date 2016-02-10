#include "stdafx.h"

#include "UnitTest++/UnitTest++.h"

int main() {

	printf("Suite: %s\n", UnitTestSuite::GetSuiteName());
	UnitTest::RunAllTests();
}