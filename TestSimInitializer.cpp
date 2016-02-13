#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"

#include "SimGraphInterface.h"
#include "SimNode.h"
#include "SimWire.h"
#include "SimInitializer.h"

using namespace hwgame;

struct SimInitializerTestFixture {

	CircuitVertex* node1;
	CircuitVertex* node2;
	CircuitVertex* node3;
	CircuitEdge* edge1;
	CircuitEdge* edge2;
	CircuitEdge* edge3;

	hwsim::SimInitializer simInit;

	SimInitializerTestFixture() {

		node1 = new CircuitVertex();
		node2 = new CircuitVertex();
		node3 = new CircuitVertex();
		edge1 = new CircuitEdge(node1, node2);
		edge2 = new CircuitEdge(node2, node3);
		edge3 = new CircuitEdge(node1, node3);

		
	};

	~SimInitializerTestFixture() {

		// this will leak memory!
		// but it doesn't really matter for one-off testing
	};

};

SUITE(SimInitializer)
{
	TEST_FIXTURE(SimInitializerTestFixture, InitTest1)
	{
		// set the default config and initState for the initializer
		simInit.defaultWireConfig = hwsim::SimWire::Config();
	}
}