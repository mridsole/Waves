#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"
#include "SimWire.h"


// well, for now let's just try a sanity test
TEST(Sanity)
{
	CHECK_EQUAL(1, 1);
}

SUITE(CircuitGraph) {

	TEST(GraphValidity) {

		using namespace hwgame;

		CircuitVertex* node1 = new CircuitVertex();
		CircuitVertex* node2 = new CircuitVertex();
		CircuitEdge* edge1 = new CircuitEdge(*node1, *node2);

		CircuitVertex* node3 = new CircuitVertex();
		
		CircuitEdge* edge2 = new CircuitEdge(*node2, *node3);
		CircuitEdge* edge3 = new CircuitEdge(*node1, *node3);

		// check some things that have to be true at this point
		CHECK(node1->edges.size() == 2);
		CHECK(node1->edges[0] == edge1);
		CHECK(node1->edges[1] == edge3);
		CHECK(&edge1->startVertex == node1);
		CHECK(&edge1->endVertex == node2);
	}
}